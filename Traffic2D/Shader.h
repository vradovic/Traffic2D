#pragma once

#include "GLError.h"
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:
	unsigned int m_Id;
	std::unordered_map<std::string, int> m_UniformLocationCache;

	int getUniformLocation(const std::string& name);
	unsigned int compileShader(unsigned int type, const std::string& filename);
	unsigned int createShader(const std::string& vertexFilename, const std::string& fragmentFilename);
public:
	Shader(const std::string& vertexFilename, const std::string& fragmentFilename);
	~Shader();

	void Bind() const;
	void Unbind() const;

	template<typename T>
	void SetUniform(const std::string& name, T value)
	{
		static_assert(false);
	}

	template<>
	void SetUniform<int>(const std::string& name, int value)
	{
		GLCall(glUniform1i(getUniformLocation(name), value));
	}
};
