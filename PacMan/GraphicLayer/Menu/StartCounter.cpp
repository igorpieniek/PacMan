#include "StartCounter.h"

void StartCounter::start(){
	if (!isTimerInitialized) {
		isStarted = true;
	}
}

void StartCounter::draw(){
	if (isStarted) {
		if (!isTimerInitialized) {
			Timer::instance().addPeriodElapsedCallback(std::bind(&StartCounter::changeTimeCb, this), 1);
			isTimerInitialized = true;
		}
		ImGui::SetNextWindowPos(ImVec2(Xpos, Ypos));
		ImGui::SetNextWindowSize(ImVec2(Xsize, Ysize));
		ImGui::Begin("startCounter", NULL, window_flags);

		ImGui::SetWindowFontScale(scale);
		ImGui::Text(std::to_string(currentTime).c_str());

		ImGui::End();
	}
}

void StartCounter::changeTimeCb(){
	isTimerInitialized = false;
	if (currentTime > 0) {
		currentTime--;
	}
	else {
		currentTime = time;
		isStarted = false;
	}
}
