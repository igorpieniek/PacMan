#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#include "ConfigLoader.h"
#include "Timer.h"

class StartCounter {
public:
	void start();
	void draw();

private:
	const float scale = 3.0f;
	const float XsizeWin = 190;
	const float YsizeWin = 200;
	const float XposWin = 0.5f * CONFIG.getMainWindowWidth() - 0.5 * XsizeWin;
	const float YposWin = 0.5f * CONFIG.getMainWindowHeight() - 0.5 * YsizeWin;

	const float YsizeText = 80;
	const float YposText = 0.5f * CONFIG.getMainWindowHeight() - 0.5 * YsizeText;
	

	int time = CONFIG.getStartDelay_s();
	int currentTime = time;
	bool isStarted = false;
	bool isTimerInitialized = false;


	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoNav |
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove;

	void changeTimeCb();
	void setTextCenter(std::string text);
};