#pragma once
#include <chrono>
#include <thread>

class Timer{
public:
	static Timer& instance();
private:
	Timer() {};
};

