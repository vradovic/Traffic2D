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
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Traffic2D"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
std::vector<float> createCircleVertices(float centerX, float centerY, float radius);

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
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader* shader = new Shader("Vertex.shader", "Fragment.shader");

	const std::vector<StreetSegment>& segments = createStreetSegments();
	StreetRenderer* renderer = new StreetRenderer(segments, shader);

	GLCall(glClearColor(0.827, 0.827, 0.827, 1.0));
	while (!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		renderer->Clear();

		renderer->Draw(GL_LINES);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	delete renderer; // shader deleted in renderer destructor
	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	GLCall(glViewport(0, 0, width, height));
}
