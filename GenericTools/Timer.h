#pragma once
#include <chrono>
#include <thread>
#include <vector>
#include <functional>

class Timer{
public:
	Timer();
	void startPeriodElapse(double duration);
	void setCallback(std::function<void()> fun);
	void reset();
	bool isLoced()const { return isWaiting; };

private:

	void process();
	void executeCallback();
	void updateTime();


	std::chrono::system_clock::time_point currentTime{};
	std::chrono::system_clock::time_point startTime{};
	std::thread thrd;

	std::function<void()> callback = nullptr;
	double requiredTime{};

	bool isWaiting = false;


};

