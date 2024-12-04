#include "StreetSegment.h"

StreetSegment::StreetSegment(const std::vector<StreetSegmentLane>& lanes)
	: m_Lanes(lanes)
{
}

std::vector<StreetSegment> createStreetSegments()
{
	std::vector<StreetSegment> segments;

	StreetSegmentLane lane1({ 0.0f, 0.0f }, { 0.5f, 0.0f }, { 1.0, 0.0, 0.0 }, 0.0f, 0.0f, 0.0f, 0.0f);
	StreetSegmentLane lane2({ 0.5f, 0.05f }, { 0.0f, 0.05f }, { 0.0, 1.0, 0.0 }, 0.0f, 0.0f, 0.0f, 0.0f);

	segments.push_back(StreetSegment({ lane1, lane2 }));

	return segments;
}
