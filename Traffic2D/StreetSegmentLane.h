#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>

struct Vertex
{
	float x;
	float y;
};

class StreetSegmentLane
{
private:
	Vertex m_Start;
	Vertex m_End;
	glm::vec3 m_Color;
	std::vector<std::shared_ptr<StreetSegmentLane>> m_ConnectedLanes;
	float m_Congestion;
	float m_CongestionRate;

	void interpolateColor();
public:
	StreetSegmentLane(Vertex start, Vertex end, float congestion, float congestionRate);
	void IncrementCongestion(float value = 0);
	void DecrementCongestion(float value = 0);

	Vertex GetStart() const { return m_Start; }
	Vertex GetEnd() const { return m_End; }
	glm::vec3 GetColor() const { return m_Color; }
	std::vector<std::shared_ptr<StreetSegmentLane>>& GetConnectedLanes() { return m_ConnectedLanes; }
	void AddLane(std::shared_ptr<StreetSegmentLane> lane) { m_ConnectedLanes.push_back(lane); }
	float GetCongestion() const { return m_Congestion; }
	float GetCongestionRate() const { return m_CongestionRate; }
};