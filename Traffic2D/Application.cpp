#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "GLError.h"
#include "StreetSegment.h"
#include "Texture.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define WINDOW_TITLE "Traffic2D"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void scrollCallback(GLFWwindow* window, double x, double y);

static bool mouseLeftHeld = false;
static bool mouseRightHeld = false;
static double mouseX = 0.0;
static double mouseY = 0.0;
static bool scrollUp = false;
static bool scrollDown = false;

int main() {
	if (!glfwInit()) {
		std::cout << "GLFW init fail" << std::endl;
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return 2;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW init fail" << std::endl;
		return 3;
	}

	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetScrollCallback(window, scrollCallback);

	Shader* shader = new Shader("Vertex.shader", "Fragment.shader");
	Shader* trafficLightShader = new Shader("Vertex.shader", "Fragment.shader");
	Shader* textureShader = new Shader("VertexTexture.shader", "FragmentTexture.shader");
	Shader* nameShader = new Shader("VertexTexture.shader", "FragmentTexture.shader");

	std::vector<StreetSegment> segments;
	createStreetSegments(segments);

	StreetRenderer* renderer = new StreetRenderer(segments, shader);
	TrafficLightRenderer* trafficLightRenderer = new TrafficLightRenderer(segments, trafficLightShader);
	TextureRenderer* textureRenderer = new TextureRenderer(textureShader);
	textureRenderer->SetTextureCoordinates(0.0f, 0.0f, 1.0f, 1.0f);

	textureShader->Bind();
	Texture texture("grb.png");
	texture.Bind();
	textureShader->SetUniform<int>("u_Texture", 0);

	GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
	GLCall(glLineWidth(10.0f));
	while (!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		if (mouseLeftHeld || mouseRightHeld)
		{
			updateLaneCongestion(mouseX, mouseY, segments, mouseLeftHeld);
		}

		if (scrollUp)
		{
			updateLaneCongestionRate(mouseX, mouseY, segments, true);
			scrollUp = false;
		}
		else if (scrollDown)
		{
			updateLaneCongestionRate(mouseX, mouseY, segments, false);
			scrollDown = false;
		}

		updateAllCongestions(segments);

		renderer->UpdateBuffer(segments);
		renderer->Clear();
		renderer->Draw(GL_LINES);

		trafficLightRenderer->UpdateBuffer(segments);
		trafficLightRenderer->Draw(GL_TRIANGLES);

		textureRenderer->Draw(GL_TRIANGLES);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	delete renderer; // Shader deleted in renderer destructor
	glfwTerminate();

	return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	GLCall(glViewport(0, 0, width, height));
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		int width, height;
		glfwGetWindowSize(window, &width, &height);

		// Normalize mouse coordinates
		mouseX = 2.0f * (xpos / width) - 1.0f;
		mouseY = 1.0f - 2.0f * (ypos / height);

		mouseLeftHeld = action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT;
		mouseRightHeld = action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_RIGHT;
	}
}

void scrollCallback(GLFWwindow* window, double x, double y)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	// Normalize mouse coordinates
	mouseX = 2.0f * (xpos / width) - 1.0f;
	mouseY = 1.0f - 2.0f * (ypos / height);

	if (y > 0)
	{
		scrollUp = true;
	}
	else if (y < 0)
	{
		scrollDown = true;
	}
}
