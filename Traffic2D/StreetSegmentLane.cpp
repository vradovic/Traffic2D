#include "StreetSegmentLane.h"

StreetSegmentLane::StreetSegmentLane(Vertex start, Vertex end, float congestion, float congestionRate)
	: m_Start(start), m_End(end), m_Congestion(congestion), m_CongestionRate(congestionRate), m_TrafficLight(TrafficLight(20.0))
{
	interpolateColor();
}

void StreetSegmentLane::IncrementCongestion(float value)
{
	if (value == 0)
	{
		value = m_CongestionRate;
	}

	if (m_Congestion + value > 1.0f)
	{
		m_Congestion = 1.0f;
	}
	else
	{
		m_Congestion += value;
	}
	interpolateColor();
}

void StreetSegmentLane::DecrementCongestion(float value)
{
	if (m_Congestion == 0.0f) return;

	if (value == 0)
	{
		value = m_CongestionRate;
	}

	if (m_Congestion - value < 0.0f)
	{
		m_Congestion = 0.0f;
	}
	else
	{
		m_Congestion -= value;
	}

	interpolateColor();
}

void StreetSegmentLane::interpolateColor()
{
	float red = (1.0f - m_Congestion) * 0.0f + m_Congestion * 1.0f;
	float green = (1.0f - m_Congestion) * 1.0f + m_Congestion * 0.0f;
	float blue = 0.0f;

	m_Color = glm::vec3(red, green, blue);
}

