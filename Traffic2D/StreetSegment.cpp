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
	auto lane11 = std::make_shared<StreetSegmentLane>(Vertex{ -0.05f, -0.1f }, Vertex{ -1.0f, -0.1f }, 0.0f, 0.005f);
	auto lane12 = std::make_shared<StreetSegmentLane>(Vertex{ 0.5f, -0.1f }, Vertex{ 0.0f, -0.1f }, 0.0f, 0.005f);
	auto lane13 = std::make_shared<StreetSegmentLane>(Vertex{ 1.0, -0.1f }, Vertex{ 0.55f, -0.1f }, 0.0f, 0.005f);
	auto lane14 = std::make_shared<StreetSegmentLane>(Vertex{ -1.0, -0.15f }, Vertex{ -0.05f, -0.15f }, 0.0f, 0.005f);
	auto lane15 = std::make_shared<StreetSegmentLane>(Vertex{ 0.0f, -0.15f }, Vertex{ 0.5f, -0.15f }, 0.0f, 0.005f);
	auto lane16 = std::make_shared<StreetSegmentLane>(Vertex{ 0.55, -0.15f }, Vertex{ 1.0f, -0.15f }, 0.0f, 0.005f);
	auto lane17 = std::make_shared<StreetSegmentLane>(Vertex{ -0.05f, -0.25f }, Vertex{ -1.0f, -0.25f }, 0.0f, 0.005f);
	auto lane18 = std::make_shared<StreetSegmentLane>(Vertex{ 0.5f, -0.25f }, Vertex{ 0.0f, -0.25f }, 0.0f, 0.005f);
	auto lane19 = std::make_shared<StreetSegmentLane>(Vertex{ 1.0, -0.25f }, Vertex{ 0.55f, -0.25f }, 0.0f, 0.005f);
	auto lane20 = std::make_shared<StreetSegmentLane>(Vertex{ -1.0, -0.3f }, Vertex{ -0.05f, -0.3f }, 0.0f, 0.005f);
	auto lane21 = std::make_shared<StreetSegmentLane>(Vertex{ 0.0f, -0.3f }, Vertex{ 0.5f, -0.3f }, 0.0f, 0.005f);
	auto lane22 = std::make_shared<StreetSegmentLane>(Vertex{ 0.55, -0.3f }, Vertex{ 1.0f, -0.3f }, 0.0f, 0.005f);
	auto lane23 = std::make_shared<StreetSegmentLane>(Vertex{ -0.05f, -0.4f }, Vertex{ -1.0, -0.4f }, 0.0f, 0.005f);
	auto lane24 = std::make_shared<StreetSegmentLane>(Vertex{ 0.5f, -0.4f }, Vertex{ 0.0f, -0.4f }, 0.0f, 0.005f);
	auto lane25 = std::make_shared<StreetSegmentLane>(Vertex{ 1.0, -0.4f }, Vertex{ 0.55f, -0.4f }, 0.0f, 0.005f);
	auto lane26 = std::make_shared<StreetSegmentLane>(Vertex{ -1.0, -0.45f }, Vertex{ -0.05f, -0.45f }, 0.0f, 0.005f);
	auto lane27 = std::make_shared<StreetSegmentLane>(Vertex{ 0.0f, -0.45f }, Vertex{ 0.5f, -0.45f }, 0.0f, 0.005f);
	auto lane28 = std::make_shared<StreetSegmentLane>(Vertex{ 0.55, -0.45f }, Vertex{ 1.0f, -0.45f }, 0.0f, 0.005f);
	auto lane29 = std::make_shared<StreetSegmentLane>(Vertex{ -0.05f, 0.0f }, Vertex{ -0.05f, -0.1f }, 0.0f, 0.005f);
	auto lane30 = std::make_shared<StreetSegmentLane>(Vertex{ -0.05f, -0.15f }, Vertex{ -0.05f, -0.25f }, 0.0f, 0.005f);
	auto lane31 = std::make_shared<StreetSegmentLane>(Vertex{ -0.05f, -0.3f }, Vertex{ -0.05f, -0.4f }, 0.0f, 0.005f);
	auto lane32 = std::make_shared<StreetSegmentLane>(Vertex{ -0.05f, -0.45f }, Vertex{ -0.05f, -1.0f }, 0.0f, 0.005f);
	auto lane33 = std::make_shared<StreetSegmentLane>(Vertex{ 0.0f, -0.1f }, Vertex{ 0.0f, 0.0f }, 0.0f, 0.005f);
	auto lane34 = std::make_shared<StreetSegmentLane>(Vertex{ 0.0f, -0.25f }, Vertex{ 0.0f, -0.15f }, 0.0f, 0.005f);
	auto lane35 = std::make_shared<StreetSegmentLane>(Vertex{ 0.0f, -0.4f }, Vertex{ 0.0f, -0.3f }, 0.0f, 0.005f);
	auto lane36 = std::make_shared<StreetSegmentLane>(Vertex{ 0.0f, -1.0f }, Vertex{ 0.0f, -0.45f }, 0.0f, 0.005f);
	auto lane37 = std::make_shared<StreetSegmentLane>(Vertex{ 0.5f, 0.0f }, Vertex{ 0.5f, -0.1f }, 0.0f, 0.005f);
	auto lane38 = std::make_shared<StreetSegmentLane>(Vertex{ 0.5f, -0.15f }, Vertex{ 0.5f, -0.25f }, 0.0f, 0.005f);
	auto lane39 = std::make_shared<StreetSegmentLane>(Vertex{ 0.5f, -0.3f }, Vertex{ 0.5f, -0.4f }, 0.0f, 0.005f);
	auto lane40 = std::make_shared<StreetSegmentLane>(Vertex{ 0.5f, -0.45f }, Vertex{ 0.5f, -1.0f }, 0.0f, 0.005f);
	auto lane41 = std::make_shared<StreetSegmentLane>(Vertex{ 0.55f, -0.1f }, Vertex{ 0.55f, 0.0f }, 0.0f, 0.005f);
	auto lane42 = std::make_shared<StreetSegmentLane>(Vertex{ 0.55f, -0.25f }, Vertex{ 0.55f, -0.15f }, 0.0f, 0.005f);
	auto lane43 = std::make_shared<StreetSegmentLane>(Vertex{ 0.55f, -0.4f }, Vertex{ 0.55f, -0.3f }, 0.0f, 0.005f);
	auto lane44 = std::make_shared<StreetSegmentLane>(Vertex{ 0.55f, -1.0f }, Vertex{ 0.55f, -0.45f }, 0.0f, 0.005f);

	lane1->AddLane(lane7);
	lane1->AddLane(lane9);
	lane1->AddLane(lane37);
	lane2->AddLane(lane3);
	lane2->AddLane(lane5);
	lane2->AddLane(lane29);
	lane4->AddLane(lane5);
	lane4->AddLane(lane1);
	lane4->AddLane(lane29);
	lane6->AddLane(lane1);
	lane6->AddLane(lane3);
	lane6->AddLane(lane29);
	lane8->AddLane(lane2);
	lane8->AddLane(lane9);
	lane8->AddLane(lane37);
	lane10->AddLane(lane2);
	lane10->AddLane(lane7);
	lane10->AddLane(lane37);
	lane14->AddLane(lane33);
	lane14->AddLane(lane15);
	lane14->AddLane(lane30);
	lane20->AddLane(lane34);
	lane20->AddLane(lane21);
	lane20->AddLane(lane31);
	lane26->AddLane(lane35);
	lane26->AddLane(lane27);
	lane26->AddLane(lane32);
	lane12->AddLane(lane33);
	lane12->AddLane(lane11);
	lane12->AddLane(lane30);
	lane15->AddLane(lane41);
	lane15->AddLane(lane16);
	lane15->AddLane(lane38);
	lane18->AddLane(lane34);
	lane18->AddLane(lane17);
	lane18->AddLane(lane31);
	lane21->AddLane(lane42);
	lane21->AddLane(lane22);
	lane21->AddLane(lane39);
	lane24->AddLane(lane35);
	lane24->AddLane(lane23);
	lane24->AddLane(lane32);
	lane27->AddLane(lane43);
	lane27->AddLane(lane28);
	lane27->AddLane(lane40);
	lane13->AddLane(lane41);
	lane13->AddLane(lane12);
	lane13->AddLane(lane38);
	lane19->AddLane(lane42);
	lane19->AddLane(lane18);
	lane19->AddLane(lane39);
	lane25->AddLane(lane43);
	lane25->AddLane(lane24);
	lane25->AddLane(lane40);
	lane29->AddLane(lane11);
	lane29->AddLane(lane30);
	lane29->AddLane(lane15);
	lane30->AddLane(lane17);
	lane30->AddLane(lane31);
	lane30->AddLane(lane21);
	lane31->AddLane(lane23);
	lane31->AddLane(lane32);
	lane31->AddLane(lane27);
	lane33->AddLane(lane3);
	lane33->AddLane(lane1);
	lane33->AddLane(lane5);
	lane34->AddLane(lane33);
	lane34->AddLane(lane15);
	lane34->AddLane(lane11);
	lane35->AddLane(lane34);
	lane35->AddLane(lane21);
	lane35->AddLane(lane17);
	lane36->AddLane(lane35);
	lane36->AddLane(lane27);
	lane36->AddLane(lane23);
	lane37->AddLane(lane12);
	lane37->AddLane(lane38);
	lane37->AddLane(lane16);
	lane38->AddLane(lane18);
	lane38->AddLane(lane39);
	lane38->AddLane(lane22);
	lane39->AddLane(lane24);
	lane39->AddLane(lane40);
	lane39->AddLane(lane28);
	lane41->AddLane(lane9);
	lane41->AddLane(lane7);
	lane41->AddLane(lane2);
	lane42->AddLane(lane16);
	lane42->AddLane(lane41);
	lane42->AddLane(lane12);
	lane43->AddLane(lane22);
	lane43->AddLane(lane42);
	lane43->AddLane(lane18);
	lane44->AddLane(lane43);
	lane44->AddLane(lane28);
	lane44->AddLane(lane24);

	segments.push_back(StreetSegment({ lane1, lane2 }));
	segments.push_back(StreetSegment({ lane3, lane4 }));
	segments.push_back(StreetSegment({ lane5, lane6 }));
	segments.push_back(StreetSegment({ lane7, lane8 }));
	segments.push_back(StreetSegment({ lane9, lane10 }));
	segments.push_back(StreetSegment({ lane11, lane14 }));
	segments.push_back(StreetSegment({ lane17, lane20 }));
	segments.push_back(StreetSegment({ lane23, lane26 }));
	segments.push_back(StreetSegment({ lane12, lane15 }));
	segments.push_back(StreetSegment({ lane13, lane16 }));
	segments.push_back(StreetSegment({ lane18, lane21 }));
	segments.push_back(StreetSegment({ lane24, lane27 }));
	segments.push_back(StreetSegment({ lane19, lane22 }));
	segments.push_back(StreetSegment({ lane25, lane28 }));
	segments.push_back(StreetSegment({ lane29, lane33 }));
	segments.push_back(StreetSegment({ lane30, lane34 }));
	segments.push_back(StreetSegment({ lane31, lane35 }));
	segments.push_back(StreetSegment({ lane32, lane36 }));
	segments.push_back(StreetSegment({ lane37, lane41 }));
	segments.push_back(StreetSegment({ lane38, lane42 }));
	segments.push_back(StreetSegment({ lane39, lane43 }));
	segments.push_back(StreetSegment({ lane40, lane44 }));
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

			if (lane->GetTrafficLightColor() == glm::vec3(0.0f, 1.0f, 0.8f))
			{ 
				lane->DecrementCongestion();
			}
		}
	}
}

void updateLaneCongestionRate(double mouseX, double mouseY, std::vector<StreetSegment>& segments, bool isIncrement)
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
					lane->IncrementCongestionRate(0.05f);
				}
				else
				{
					lane->DecrementCongestionRate(0.05f);
				}
			}
		}
	}
}
