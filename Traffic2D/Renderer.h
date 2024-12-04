#pragma once

#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "StreetSegment.h"

class Renderer
{
public:
	virtual void Draw(int mode) const = 0;
	void Clear() const;
};

class StreetRenderer : public Renderer
{
private:
	VertexArray* m_VA;
	VertexBuffer* m_VB;
	IndexBuffer* m_IB;
	Shader* m_Shader;
public:
	StreetRenderer(const std::vector<StreetSegment>& segments, Shader* shader);
	~StreetRenderer();
	void Draw(int mode) const;
};
