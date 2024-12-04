#include "StreetSegmentLane.h"

StreetSegmentLane::StreetSegmentLane(Vertex start, Vertex end, glm::vec3 color, float congestion, float congestionRate, float congestionStep, float congestionRateStep)
	: m_Start(start), m_End(end), m_Color(color), m_Congestion(congestion), m_CongestionRate(congestionRate), m_CongestionStep(congestionStep), m_CongestionRateStep(congestionRateStep)
{
}

void StreetSegmentLane::IncrementCongestion()
{
	m_Congestion += m_CongestionStep;
}

void StreetSegmentLane::DecrementCongestion()
{
	m_Congestion -= m_CongestionStep;
}

void StreetSegmentLane::IncrementCongestionRate()
{
	m_CongestionRate += m_CongestionRateStep;
}

void StreetSegmentLane::DecrementCongestionRate()
{
	m_CongestionRate -= m_CongestionRateStep;
}
