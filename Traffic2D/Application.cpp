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

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Traffic2D"

unsigned int compileShader(GLenum type, const char* source);
unsigned int createShader(const char* vsSource, const char* fsSource);
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

	GLCall(glClearColor(0.827, 0.827, 0.827, 1.0));

	// BUFFER SETUP

	unsigned int vao;
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	// STREET SEGMENTS

	float vertices[] = {
		-0.75, 1.0,
		-0.25, 1.0,
		 0.25, 1.0,
		 0.75, 1.0,

		 -1.0, 0.75,
		-0.75, 0.75,
		-0.25, 0.75,
		 0.25, 0.75,
		 0.75, 0.75,
		  1.0, 0.75,

		 -1.0, 0.25,
		-0.75, 0.25,
		-0.25, 0.25,
		 0.25, 0.25,
		 0.75, 0.25,
		  1.0, 0.25,

		 -1.0, -0.25,
		-0.75, -0.25,
		-0.25, -0.25,
		 0.25, -0.25,
		 0.75, -0.25,
		  1.0, -0.25,

		 -1.0, -0.75,
		-0.75, -0.75,
		-0.25, -0.75,
		 0.25, -0.75,
		 0.75, -0.75,
		  1.0, -0.75,

		-0.75, -1.0,
		-0.25, -1.0,
		 0.25, -1.0,
		 0.75, -1.0,
	};

	unsigned int indices[] = {
		4, 5, 5, 6, 6, 7, 7, 8, 8, 9,
		10, 11, 11, 12, 12, 13, 13, 14, 14, 15,
		16, 17, 17, 18, 18, 19, 19, 20, 20, 21,
		22, 23, 23, 24, 24, 25, 25, 26, 26, 27,

		0, 5, 5, 11, 11, 17, 17, 23, 23, 28,
		1, 6, 6, 12, 12, 18, 18 ,24, 24, 29,
		2, 7, 7, 13, 13, 19, 19, 25, 25, 30,
		3, 8, 8, 14, 14, 20, 20, 26, 26, 31
	};

	VertexBuffer* vb = new VertexBuffer(vertices, sizeof(vertices));

	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL));
	GLCall(glEnableVertexAttribArray(0));

	IndexBuffer* ib = new IndexBuffer(indices, sizeof(indices));

	vb->Unbind();
	ib->Unbind();
	GLCall(glBindVertexArray(0));

	// TRAFFIC LIGHT CIRCLE

	unsigned int circleVao;
	GLCall(glGenVertexArrays(1, &circleVao));
	GLCall(glBindVertexArray(circleVao));

	std::vector<float> circleVertices = createCircleVertices(0.5, 0.5, 0.03);

	unsigned int circleVbo;
	GLCall(glGenBuffers(1, &circleVbo));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, circleVbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, circleVertices.size() * sizeof(float), circleVertices.data(), GL_STATIC_DRAW));

	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0));
	GLCall(glEnableVertexAttribArray(0));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));

	// SHADER PROGRAM

	unsigned int shader = createShader("Vertex.shader", "Fragment.shader");
	GLCall(glUseProgram(shader));

	GLCall(glLineWidth(2.0));

	GLCall(glUseProgram(0));

	// MAIN LOOP

	while (!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		GLCall(glUseProgram(shader));
		GLCall(glBindVertexArray(vao));
		GLCall(glDrawElements(GL_LINES, 80, GL_UNSIGNED_INT, indices));
		GLCall(glBindVertexArray(circleVao));
		GLCall(glDrawArrays(GL_TRIANGLE_FAN, 0, circleVertices.size()));

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	delete vb;
	delete ib;
	glfwTerminate();

	return 0;
}

unsigned int compileShader(GLenum type, const char* source) {
	std::string content = "";
	std::ifstream file(source);
	std::stringstream ss;
	if (file.is_open()) {
		ss << file.rdbuf();
		file.close();
		std::cout << "Success reading from: " << source << std::endl;
	} else {
		ss << "";
		std::cout << "Failed to read from: " << source << std::endl;
	}
	std::string temp = ss.str();
	const char* sourceCode = temp.c_str();

	int shader = glCreateShader(type);

	int success;
	char infoLog[512];
	GLCall(glShaderSource(shader, 1, &sourceCode, NULL));
	GLCall(glCompileShader(shader));

	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
	if (success == GL_FALSE) {
		GLCall(glGetShaderInfoLog(shader, 512, NULL, infoLog));
		if (type == GL_VERTEX_SHADER)
			printf("VERTEX");
		else if (type == GL_FRAGMENT_SHADER)
			printf("FRAGMENT");
		printf(" error: \n");
		printf(infoLog);
	}

	return shader;
}

unsigned int createShader(const char* vsSource, const char* fsSource) {
	unsigned int program;
	unsigned int vertexShader;
	unsigned int fragmentShader;

	program = glCreateProgram();

	vertexShader = compileShader(GL_VERTEX_SHADER, vsSource);
	fragmentShader = compileShader(GL_FRAGMENT_SHADER, fsSource);

	GLCall(glAttachShader(program, vertexShader));
	GLCall(glAttachShader(program, fragmentShader));

	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	int success;
	char infoLog[512];
	GLCall(glGetProgramiv(program, GL_VALIDATE_STATUS, &success));
	if (success == GL_FALSE) {
		GLCall(glGetShaderInfoLog(program, 512, NULL, infoLog));
		std::cout << "Shader error: \n";
		std::cout << infoLog << std::endl;
	}

	GLCall(glDetachShader(program, vertexShader));
	GLCall(glDeleteShader(vertexShader));
	GLCall(glDetachShader(program, fragmentShader));
	GLCall(glDeleteShader(fragmentShader));

	return program;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	GLCall(glViewport(0, 0, width, height));
}

std::vector<float> createCircleVertices(float centerX, float centerY, float radius) {
	std::vector<float> vertices;
    const int numSegments = 12;
    const float twicePi = 2.0f * 3.14159f;

    // Generate vertices for circle triangles
    for (int i = 0; i <= numSegments; ++i) {
        float angle = (i * twicePi) / numSegments;
        float x = centerX + (radius * std::cos(angle));
        float y = centerY + (radius * std::sin(angle));
        vertices.push_back(x);
        vertices.push_back(y);
    }

    return vertices;
}
