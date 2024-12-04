#include "StreetSegment.h"

StreetSegment::StreetSegment(const std::vector<StreetSegmentLane>& lanes)
	: m_Lanes(lanes)
{
}

std::vector<StreetSegment> createStreetSegments()
{
	std::vector<StreetSegment> segments;

	StreetSegmentLane lane1({ 0.0f, 0.0f }, { 0.5f, 0.0f }, 0.0f, 0.0f, 0.01f, 0.0f);
	StreetSegmentLane lane2({ 0.5f, 0.05f }, { 0.0f, 0.05f }, 0.0f, 0.0f, 0.01f, 0.0f);

	segments.push_back(StreetSegment({ lane1, lane2 }));

	return segments;
}

void updateLaneCongestion(double mouseX, double mouseY, std::vector<StreetSegment>& segments, bool isIncrement)
{
	const float buffer = 0.01f;
	for (StreetSegment& segment : segments)
	{
		for (StreetSegmentLane& lane : segment.GetLanes())
		{
			double laneStartX = lane.GetStart().x;
			double laneEndX = lane.GetEnd().x;
			double laneStartY = lane.GetStart().y;
			double laneEndY = lane.GetEnd().y;

			if (laneStartX > laneEndX)
			{
				std::swap(laneStartX, laneEndX);
			}

			if (laneStartY > laneEndY)
			{
				std::swap(laneStartY, laneEndY);
			}

			if (mouseX >= laneStartX - buffer && mouseX <= laneEndX + buffer &&
				mouseY >= laneStartY - buffer && mouseY <= laneEndY + buffer)
			{
				if (isIncrement)
				{
					lane.IncrementCongestion();
				}
				else 
				{
					lane.DecrementCongestion();
				}
			}
		}
	}
}
