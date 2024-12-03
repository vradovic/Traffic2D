#pragma once

class StreetSegmentLane
{
private:
	float m_Congestion;
	float m_CongestionRate;
	float m_CongestionStep;
	float m_CongestionRateStep;
public:
	StreetSegmentLane(float congestion, float congestionRate, float congestionStep, float congestionRateStep);
	void IncrementCongestion();
	void DecrementCongestion();
	void IncrementCongestionRate();
	void DecrementCongestionRate();
};