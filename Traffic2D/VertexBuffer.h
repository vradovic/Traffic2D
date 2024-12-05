#pragma once

#include <vector>

class VertexBuffer {
private:
	unsigned int m_Id;
	std::vector<float> m_Data;
public:
	VertexBuffer(const std::vector<float>& data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
	void UpdateData(const std::vector<float>& data, unsigned int size);
};