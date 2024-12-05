#pragma once

#include <atomic>
#include <thread>
#include <chrono>
#include <mutex>
#include <iostream>

class TrafficLight
{
private:
	int m_Time;
	std::atomic<char> m_Color; // 0 = red, 1 = green
	std::atomic<bool> m_Running;
	std::mutex m_Mutex;

	void safeLog(const std::string& message) {
		std::lock_guard<std::mutex> lock(m_Mutex);
		std::cout << message << std::endl;
	}
public:
	TrafficLight(int time);
	void Run();
	void Stop() { m_Running = false; }
	char GetColor() const { return m_Color; }
};
