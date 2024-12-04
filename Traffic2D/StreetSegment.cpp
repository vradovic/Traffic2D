#include "StreetSegment.h"

#include <iostream>

StreetSegment::StreetSegment(const std::vector<std::shared_ptr<StreetSegmentLane>>& lanes)
	: m_Lanes(lanes)
{
}

void createStreetSegments(std::vector<StreetSegment>& segments)
{
	auto lane1 = std::make_shared<StreetSegmentLane>(Vertex{ 0.0f, 0.0f }, Vertex{ 0.5f, 0.0f }, 0.0f, 0.0f, 0.01f, 0.0f);
	auto lane2 = std::make_shared<StreetSegmentLane>(Vertex{ 0.5f, 0.05f }, Vertex{ 0.0f, 0.05f }, 0.0f, 0.0f, 0.01f, 0.0f);
	auto lane3 = std::make_shared<StreetSegmentLane>(Vertex{ 0.0f, 0.05f }, Vertex{ 0.0f, 1.0f }, 0.0f, 0.0f, 0.01f, 0.0f);
	auto lane4 = std::make_shared<StreetSegmentLane>(Vertex{ -0.05f, 1.0f }, Vertex{ -0.05f, 0.05f }, 0.0f, 0.0f, 0.01f, 0.0f);

	lane2->AddLane(lane3);

	segments.push_back(StreetSegment({ lane1, lane2 }));
	segments.push_back(StreetSegment({ lane3, lane4 }));
}

void updateLaneCongestion(double mouseX, double mouseY, std::vector<StreetSegment>& segments, bool isIncrement)
{
	const float buffer = 0.01f;
	for (StreetSegment& segment : segments)
	{
		for (auto lane : segment.GetLanes())
		{
			double laneStartX = lane->GetStart().x;
			double laneEndX = lane->GetEnd().x;
			double laneStartY = lane->GetStart().y;
			double laneEndY = lane->GetEnd().y;

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
					lane->IncrementCongestion();
				}
				else 
				{
					lane->DecrementCongestion();
				}
			}
		}
	}
}

void updateAllCongestions(std::vector<StreetSegment>& segments)
{
	for (StreetSegment& segment : segments)
	{
		for (auto lane : segment.GetLanes())
		{
			if (lane->GetConnectedLanes().size() < 1)
			{
				continue;
			}

			lane->DecrementCongestion();
		}
	}
}
