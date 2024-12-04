#include "Shader.h"
#include "GLError.h"
#include <iostream>
#include <fstream>
#include <sstream>

int Shader::getUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];
	}

    GLCall(int location = glGetUniformLocation(m_Id, name.c_str()));
	if (location == -1)
	{
		std::cout << "Uniform " << name << " does not exist." << std::endl;
	}
	
	m_UniformLocationCache[name] = location;
	
	return location;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& filename) {
	std::string content = "";
	std::ifstream file(filename);
	std::stringstream ss;
	if (file.is_open()) {
		ss << file.rdbuf();
		file.close();
		std::cout << "Success reading from: " << filename << std::endl;
	}
	else {
		ss << "";
		std::cout << "Failed to read from: " << filename << std::endl;
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

unsigned int Shader::createShader(const std::string& vertexFilename, const std::string& fragmentFilename) {
	unsigned int program;
	unsigned int vertexShader;
	unsigned int fragmentShader;

	program = glCreateProgram();

	vertexShader = compileShader(GL_VERTEX_SHADER, vertexFilename);
	fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentFilename);

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

Shader::Shader(const std::string& vertexFilename, const std::string& fragmentFilename)
    : m_Id(0)
{
	m_Id = createShader(vertexFilename, fragmentFilename);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_Id));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_Id));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}


template<>
void Shader::SetUniform<float[2][3]>(const std::string& name, float values[2][3])
{
	GLCall(glUniform3fv(getUniformLocation(name), 1, &values[0][0]));
}
