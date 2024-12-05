#include "StreetSegment.h"

#include <iostream>

StreetSegment::StreetSegment(const std::vector<std::shared_ptr<StreetSegmentLane>>& lanes)
	: m_Lanes(lanes)
{
}

void createStreetSegments(std::vector<StreetSegment>& segments)
{
	auto lane1 = std::make_shared<StreetSegmentLane>(Vertex{ 0.0f, 0.0f }, Vertex{ 0.5f, 0.0f }, 0.0f, 0.005f);
	auto lane2 = std::make_shared<StreetSegmentLane>(Vertex{ 0.5f, 0.05f }, Vertex{ 0.0f, 0.05f }, 0.0f, 0.005f);
	auto lane3 = std::make_shared<StreetSegmentLane>(Vertex{ 0.0f, 0.05f }, Vertex{ 0.0f, 1.0f }, 0.0f, 0.005f);
	auto lane4 = std::make_shared<StreetSegmentLane>(Vertex{ -0.05f, 1.0f }, Vertex{ -0.05f, 0.05f }, 0.0f, 0.005f);
	auto lane5 = std::make_shared<StreetSegmentLane>(Vertex{ -0.05f, 0.05f }, Vertex{ -1.0f, 0.05f }, 0.0f, 0.005f);
	auto lane6 = std::make_shared<StreetSegmentLane>(Vertex{ -1.0, 0.0f }, Vertex{ -0.05f, 0.0f }, 0.0f, 0.005f);
	auto lane7 = std::make_shared<StreetSegmentLane>(Vertex{ 0.55, 0.0f }, Vertex{ 1.0f, 0.0f }, 0.0f, 0.005f);
	auto lane8 = std::make_shared<StreetSegmentLane>(Vertex{ 1.0, 0.05f }, Vertex{ 0.55f, 0.05f }, 0.0f, 0.005f);
	auto lane9 = std::make_shared<StreetSegmentLane>(Vertex{ 0.55f, 0.05f }, Vertex{ 0.55f, 1.0f }, 0.0f, 0.005f);
	auto lane10 = std::make_shared<StreetSegmentLane>(Vertex{ 0.5f, 1.0f }, Vertex{ 0.5f, 0.05f }, 0.0f, 0.005f);

	lane1->AddLane(lane7);
	lane2->AddLane(lane3);
	lane2->AddLane(lane5);
	lane4->AddLane(lane5);
	lane6->AddLane(lane1);
	lane8->AddLane(lane2);
	lane8->AddLane(lane9);
	lane10->AddLane(lane2);

	segments.push_back(StreetSegment({ lane1, lane2 }));
	segments.push_back(StreetSegment({ lane3, lane4 }));
	segments.push_back(StreetSegment({ lane5, lane6 }));
	segments.push_back(StreetSegment({ lane7, lane8 }));
	segments.push_back(StreetSegment({ lane9, lane10 }));
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
					lane->IncrementCongestion(0.05f);
				}
				else 
				{
					lane->DecrementCongestion(0.05f);
				}
			}
		}
	}
}

void updateAllCongestions(std::vector<StreetSegment>& segments)
{
	for (StreetSegment& segment : segments)
	{
		for (std::shared_ptr<StreetSegmentLane> lane : segment.GetLanes())
		{
			std::vector<std::shared_ptr<StreetSegmentLane>> connectedLanes = lane->GetConnectedLanes();
			std::vector<std::shared_ptr<StreetSegmentLane>> availableLanes;

			if (connectedLanes.empty())
			{
				if (lane->GetCongestion() > 0.0f)
				{
					lane->DecrementCongestion(0.001f);
				}

				continue;
			}

			for (std::shared_ptr<StreetSegmentLane> connectedLane : connectedLanes)
			{
				if (connectedLane->GetCongestion() < 1.0f)
				{
					availableLanes.push_back(connectedLane);
				}
			}

			if (availableLanes.empty()) continue;

			if (lane->GetCongestion() == 0.0f) continue;

			lane->DecrementCongestion();

			float nextAmount = lane->GetCongestionRate() / availableLanes.size();

			for (std::shared_ptr<StreetSegmentLane> availableLane : availableLanes)
			{
				availableLane->IncrementCongestion(nextAmount);
			}
		}
	}
}
