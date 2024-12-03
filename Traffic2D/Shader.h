#pragma once

#include <string>
#include <unordered_map>

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

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
};
