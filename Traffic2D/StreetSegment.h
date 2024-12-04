#pragma once

#include <vector>
#include "StreetSegmentLane.h"

class StreetSegment
{
private:
	std::vector<StreetSegmentLane> m_Lanes;
public:
	StreetSegment(const std::vector<StreetSegmentLane>& lanes);
	
	inline const std::vector<StreetSegmentLane>& GetLanes() const { return m_Lanes; }
};

std::vector<StreetSegment> createStreetSegments();
