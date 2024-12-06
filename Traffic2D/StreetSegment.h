#pragma once

#include <vector>
#include "StreetSegmentLane.h"
#include <memory>

class StreetSegment
{
private:
	std::vector<std::shared_ptr<StreetSegmentLane>> m_Lanes;
public:
	StreetSegment(const std::vector<std::shared_ptr<StreetSegmentLane>>& lanes);
	
	std::vector<std::shared_ptr<StreetSegmentLane>>& GetLanes() { return m_Lanes; }
};

void createStreetSegments(std::vector<StreetSegment>& segments);

void updateLaneCongestion(double mouseX, double mouseY, std::vector<StreetSegment>& segments, bool isIncrement);
void updateAllCongestions(std::vector<StreetSegment>& segments);
void updateLaneCongestionRate(double mouseX, double mouseY, std::vector<StreetSegment>& segments, bool isIncrement);
