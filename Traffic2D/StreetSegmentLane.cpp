#include "StreetSegmentLane.h"
#include <thread>

StreetSegmentLane::StreetSegmentLane(Vertex start, Vertex end, float congestion, float congestionRate)
	: m_Start(start), m_End(end), m_Congestion(congestion), m_CongestionRate(congestionRate), m_TrafficLight(rand() % (40 - 20 + 1) + 20)
{
	m_TrafficLightThread = std::thread(&TrafficLight::Run, &m_TrafficLight);

	interpolateColor();
}

StreetSegmentLane::~StreetSegmentLane()
{
	m_TrafficLight.Stop();
	m_TrafficLightThread.join();
}

void StreetSegmentLane::IncrementCongestion(float value)
{
	if (value == 0)
	{
		value = m_CongestionRate;
	}

	if (m_Congestion + value > 1.0f)
	{
		m_Congestion = 1.0f;
	}
	else
	{
		m_Congestion += value;
	}
	interpolateColor();
}

void StreetSegmentLane::DecrementCongestion(float value)
{
	if (m_Congestion == 0.0f) return;

	if (m_TrafficLight.GetColor() == 0 && m_ConnectedLanes.size() > 0) return;

	if (value == 0)
	{
		value = m_CongestionRate;
	}

	if (m_Congestion - value < 0.0f)
	{
		m_Congestion = 0.0f;
	}
	else
	{
		m_Congestion -= value;

		for (std::shared_ptr<StreetSegmentLane> lane : m_ConnectedLanes)
		{
			if (m_TrafficLight.GetColor() == 0) continue;
			lane->IncrementCongestion(value / m_ConnectedLanes.size());
		}
	}

	interpolateColor();
}

void StreetSegmentLane::IncrementCongestionRate(float value)
{
	if (m_CongestionRate + value > 1.0f)
	{
		m_CongestionRate = 1.0f;
	}
	else
	{
		m_CongestionRate += value;
	}
}

void StreetSegmentLane::DecrementCongestionRate(float value)
{
	if (m_CongestionRate - value < 0.0f)
	{
		m_CongestionRate = 0.0f;
	}
	else
	{
		m_CongestionRate -= value;
	}
}

glm::vec3 StreetSegmentLane::GetTrafficLightColor() const
{
	switch (m_TrafficLight.GetColor())
	{
	case 0:
		return glm::vec3(1.0f, 0.0f, 0.0f);
	case 1:
		return glm::vec3(0.0f, 1.0f, 0.8f);
	default:
		return glm::vec3(1.0f, 0.8f, 0.0f);
	};
}

void StreetSegmentLane::interpolateColor()
{
	float red = (1.0f - m_Congestion) * 0.0f + m_Congestion * 1.0f;
	float green = (1.0f - m_Congestion) * 1.0f + m_Congestion * 0.0f;
	float blue = 0.0f;

	m_Color = glm::vec3(red, green, blue);
}

