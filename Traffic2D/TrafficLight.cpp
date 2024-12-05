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

		int sleepTime;
		switch (m_Color)
		{
		case 0:
			sleepTime = m_Time;
			break;
		case 1:
			sleepTime = m_Time / 2;
			break;
		default:
			sleepTime = 3;
		}
		std::this_thread::sleep_for(std::chrono::seconds((int)sleepTime));

		if (m_Color == 0)
		{
			m_Color = 2;
		}
		else if (m_Color == 1)
		{
			m_Color = 3;
		}
		else if (m_Color == 2)
		{
			m_Color = 1;
		}
		else
		{
			m_Color = 0;
		}
	}
}
