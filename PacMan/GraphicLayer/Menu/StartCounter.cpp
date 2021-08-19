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
		ImGui::SetNextWindowPos(ImVec2(XposWin, YposWin));
		ImGui::SetNextWindowSize(ImVec2(XsizeWin, YsizeWin));
		ImGui::Begin("startCounterWind", NULL, window_flags);

		ImGui::End();

		ImGui::SetNextWindowPos(ImVec2(XposWin, YposText));
		ImGui::SetNextWindowSize(ImVec2(XsizeWin, YsizeText));
		ImGui::Begin("startCounter", NULL, window_flags | ImGuiWindowFlags_NoBackground );
		ImGui::SetWindowFontScale(scale);
		
		if (currentTime == 0) {
			setTextCenter("START!");
		}
		else {
			setTextCenter(std::to_string(currentTime));
		}
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

void StartCounter::setTextCenter(std::string text) {
	float font_size = ImGui::GetFontSize() * text.size() / 2;
	ImGui::SameLine(
		ImGui::GetWindowSize().x / 2 -
		font_size + (font_size / 2)
	);

	ImGui::Text(text.c_str());
}
