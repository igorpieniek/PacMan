#pragma once
#include <chrono>
#include <thread>
#include <vector>
#include <functional>

class Timer{
public:
	static Timer& instance();

	void addPeriodElapsedCallback(std::function<void()> fun,double sec);

private:
	Timer();
	void process();
	void deleteUsedCallbacks();
	void executeCallbacks();
	void updateTime();


	std::chrono::system_clock::time_point  currentTime;
	std::thread thrd;

	struct CallbackElement {
		std::function<void()> fun;
		double requiredTime;
		std::chrono::system_clock::time_point startTime;
		bool isUsed = false;
	};

	std::vector<CallbackElement> callbacks;
};

