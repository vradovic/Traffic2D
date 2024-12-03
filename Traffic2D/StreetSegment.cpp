#include "StreetSegment.h"

StreetSegment::StreetSegment(Vertex vertexA, Vertex vertexB)
	: m_VertexA(vertexA), m_VertexB(vertexB)
{
}

void StreetSegment::AddLinkedSegment(const StreetSegment& ss)
{
	m_LinkedSegments.push_back(ss);
}

const std::vector<StreetSegment>& createStreetSegments()
{
	std::vector<StreetSegment> segments;

	return segments;
}
