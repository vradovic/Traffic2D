#pragma once

#include <vector>
#include "StreetSegmentLane.h"

class StreetSegment
{
private:
	std::vector<StreetSegmentLane> m_Lanes;
public:
	StreetSegment(const std::vector<StreetSegmentLane>& lanes);
	
	inline std::vector<StreetSegmentLane>& GetLanes() { return m_Lanes; }
};

std::vector<StreetSegment> createStreetSegments();

void updateLaneCongestion(double mouseX, double mouseY, std::vector<StreetSegment>& segments, bool isIncrement);
