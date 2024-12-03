#pragma once

#include <vector>

struct Vertex
{
	float x, y;
};

class StreetSegment
{
private:
	std::vector<StreetSegment> m_LinkedSegments;
	Vertex m_VertexA, m_VertexB;
public:
	StreetSegment(Vertex vertexA, Vertex vertexB);
	void AddLinkedSegment(const StreetSegment& ss);
};

const std::vector<StreetSegment>& createStreetSegments();
