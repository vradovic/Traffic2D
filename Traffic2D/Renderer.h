#pragma once

#include "VertexArray.h"
#include "Shader.h"

class Renderer
{
public:
	void Draw(const VertexArray& va, unsigned int count, const Shader& shader, int mode) const;
	void Clear() const;
};
