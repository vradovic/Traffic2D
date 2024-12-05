#pragma once

#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "StreetSegment.h"

class Renderer
{
protected:
	VertexArray* m_VA;
	VertexBuffer* m_VB;
	IndexBuffer* m_IB;
	Shader* m_Shader;
public:
	~Renderer();
	virtual void Draw(int mode) const;
	void Clear() const;
};

class StreetRenderer : public Renderer
{
public:
	StreetRenderer(const std::vector<StreetSegment>& segments, Shader* shader);
	void UpdateBuffer(const std::vector<StreetSegment>& segments);
};

class TrafficLightRenderer : public Renderer
{
public:
	TrafficLightRenderer(const std::vector<StreetSegment>& segments, Shader* shader);
	void UpdateBuffer(const std::vector<StreetSegment>& segments);
};

class LogoRenderer : public Renderer
{
public:
	LogoRenderer(Shader* shader);
};
