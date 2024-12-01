#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Traffic2D"

#define ASSERT(x) if (!(x)) assert(false)

#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLCheckError())

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLCheckError()
{
	while (GLenum error = glGetError())
	{

		std::cout << "[OpenGL Error] ";
		switch (error) {
		case GL_INVALID_ENUM:
			std::cout << "GL_INVALID_ENUM : An unacceptable value is specified for an enumerated argument.";
			break;
		case GL_INVALID_VALUE:
			std::cout << "GL_INVALID_OPERATION : A numeric argument is out of range.";
			break;
		case GL_INVALID_OPERATION:
			std::cout << "GL_INVALID_OPERATION : The specified operation is not allowed in the current state.";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION : The framebuffer object is not complete.";
			break;
		case GL_OUT_OF_MEMORY:
			std::cout << "GL_OUT_OF_MEMORY : There is not enough memory left to execute the command.";
			break;
		case GL_STACK_UNDERFLOW:
			std::cout << "GL_STACK_UNDERFLOW : An attempt has been made to perform an operation that would cause an internal stack to underflow.";
			break;
		case GL_STACK_OVERFLOW:
			std::cout << "GL_STACK_OVERFLOW : An attempt has been made to perform an operation that would cause an internal stack to overflow.";
			break;
		default:
			std::cout << "Unrecognized error" << error;
		}
		std::cout << std::endl;
		return false;
	}
	return true;
}

unsigned int compileShader(GLenum type, const char* source);
unsigned int createShader(const char* vsSource, const char* fsSource);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

struct Vertex {
	float x, y;
};

struct StreetSegment {
	Vertex a, b;
};

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

	unsigned int vbo;
	GLCall(glGenBuffers(1, &vbo));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL));
	GLCall(glEnableVertexAttribArray(0));

	unsigned int ibo;
	GLCall(glGenBuffers(1, &ibo));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

	unsigned int shader = createShader("Vertex.shader", "Fragment.shader");
	GLCall(glUseProgram(shader));

	GLCall(glUseProgram(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));

	GLCall(glLineWidth(2.0));

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

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

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
