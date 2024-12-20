#include "VertexBuffer.h"
#include "GLError.h"

VertexBuffer::VertexBuffer(const std::vector<float>& data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_Id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data.data(), GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_Id));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Id));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::UpdateData(const std::vector<float>& data, unsigned int size)
{
	m_Data = data;
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data.data()));
}
