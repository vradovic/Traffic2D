#include "TrafficLight.h"

TrafficLight::TrafficLight(int time)
	: m_Time(time), m_Color(0), m_Running(true)
{
}

void TrafficLight::Run()
{
	while (m_Running)
	{
		safeLog("Traffic light is " + std::string(m_Color == 0 ? "RED" : "GREEN"));

		double sleepTime = m_Color == 0 ? m_Time : m_Time / 2;
		std::this_thread::sleep_for(std::chrono::seconds((int)sleepTime));

		if (m_Color == 0)
		{
			m_Color = 1;
		}
		else
		{
			m_Color = 0;
		}
	}
}
