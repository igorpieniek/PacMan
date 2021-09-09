#include "StartCounter.h"

StartCounter::StartCounter(){
	counterTimer.setCallback(std::bind(&StartCounter::changeTimeCb, this));
}

void StartCounter::start(){
	if (!isTimerInitialized) {
		isStarted = true;
	}
}

void StartCounter::draw(){
	if (isStarted) {
		if (!isTimerInitialized) {
			counterTimer.startPeriodElapse(1);
			isTimerInitialized = true;
		}
		ImGui::SetNextWindowPos(ImVec2(XposWin, YposWin));
		ImGui::SetNextWindowSize(ImVec2(XsizeWin, YsizeWin));
		ImGui::Begin("startCounterWind", NULL, window_flags);

		ImGui::End();

		ImGui::SetNextWindowPos(ImVec2(XposWin, YposText));
		ImGui::SetNextWindowSize(ImVec2(XsizeWin, YsizeText));
		ImGui::Begin("startCounter", NULL, window_flags | ImGuiWindowFlags_NoBackground );
		ImGui::SetWindowFontScale(currentScale);
		
		std::string msg;
		
		if (currentTime == 0) {
			msg = "START!";
		}
		else {
			msg = std::to_string(currentTime);
		}
		setTextCenter(msg);
		ImGui::TextColored(ImVec4(1, 1, 0, currentOpacity), msg.c_str());
		ImGui::End();
		currentOpacity -= opacityStep;
		currentScale += scaleStep;
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
	currentOpacity = opacity;
	currentScale = scale;
}

void StartCounter::setTextCenter(std::string text) {
	float font_size = ImGui::GetFontSize() * text.size() / 2;
	ImGui::SameLine(
		ImGui::GetWindowSize().x / 2 -
		font_size + (font_size / 2)
	);
}
