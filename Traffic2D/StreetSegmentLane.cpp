#include "StreetSegmentLane.h"

StreetSegmentLane::StreetSegmentLane(Vertex start, Vertex end, float congestion, float congestionRate, float congestionStep, float congestionRateStep)
	: m_Start(start), m_End(end), m_Congestion(congestion), m_CongestionRate(congestionRate), m_CongestionStep(congestionStep), m_CongestionRateStep(congestionRateStep)
{
	interpolateColor();
}

void StreetSegmentLane::IncrementCongestion()
{
	if (m_Congestion + m_CongestionStep > 1.0f)
	{
		m_Congestion = 1.0f;
	}
	else
	{
		m_Congestion += m_CongestionStep;
	}
	interpolateColor();
}

void StreetSegmentLane::DecrementCongestion()
{
	if (m_Congestion - m_CongestionStep < 0.0f)
	{
		m_Congestion = 0.0f;
	}
	else
	{
		m_Congestion -= m_CongestionStep;
	}
	interpolateColor();
}

void StreetSegmentLane::IncrementCongestionRate()
{
	m_CongestionRate += m_CongestionRateStep;
}

void StreetSegmentLane::DecrementCongestionRate()
{
	m_CongestionRate -= m_CongestionRateStep;
}

void StreetSegmentLane::interpolateColor()
{
	float red = (1.0f - m_Congestion) * 0.0f + m_Congestion * 1.0f;
	float green = (1.0f - m_Congestion) * 1.0f + m_Congestion * 0.0f;
	float blue = 0.0f;

	m_Color = glm::vec3(red, green, blue);
}

