#pragma once

#include <glm/glm.hpp>

struct Vertex
{
	float x;
	float y;
};

class StreetSegmentLane
{
private:
	Vertex m_Start;
	Vertex m_End;
	glm::vec3 m_Color;
	float m_Congestion;
	float m_CongestionRate;
	float m_CongestionStep;
	float m_CongestionRateStep;
public:
	StreetSegmentLane(Vertex start, Vertex end, glm::vec3 color, float congestion, float congestionRate, float congestionStep, float congestionRateStep);
	void IncrementCongestion();
	void DecrementCongestion();
	void IncrementCongestionRate();
	void DecrementCongestionRate();

	inline Vertex GetStart() const { return m_Start; }
	inline Vertex GetEnd() const { return m_End; }
	inline glm::vec3 GetColor() const { return m_Color; }
};