#include "Renderer.h"
#include "GLError.h"

void Renderer::Draw(const VertexArray& va, unsigned int count, const Shader& shader, int mode) const
{
	shader.Bind();
	va.Bind();
	GLCall(glDrawElements(mode, count, GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
