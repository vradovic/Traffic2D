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

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define WINDOW_TITLE "Traffic2D"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

static bool mouseLeftHeld = false;
static bool mouseRightHeld = false;
static double mouseX = 0.0;
static double mouseY = 0.0;

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

	Shader* shader = new Shader("Vertex.shader", "Fragment.shader");

	std::vector<StreetSegment> segments = createStreetSegments();
	StreetRenderer* renderer = new StreetRenderer(segments, shader);

	GLCall(glClearColor(0.827, 0.827, 0.827, 1.0));
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
			renderer->UpdateBuffer(segments);
		}
		else if (mouseRightHeld)
		{
			// Decrement lane congestion
		}

		renderer->Clear();

		renderer->Draw(GL_LINES);

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
