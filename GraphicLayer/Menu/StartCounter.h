#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#include "ConfigLoader.h"
#include "Timer.h"

class StartCounter {
public:
	StartCounter();
	void start();
	void draw();

private:

	const float XsizeWin = (float)(CONFIG.getMainWindowWidth()-10);
	const float YsizeWin = 220;
	const float XposWin = 0.5f * CONFIG.getMainWindowWidth() - 0.5f * XsizeWin;
	const float YposWin = 0.5f * CONFIG.getMainWindowHeight() - 0.5f * YsizeWin;

	const float YsizeText = 80;
	const float YposText = 0.5f * CONFIG.getMainWindowHeight() - 0.5f * YsizeText;
	
	const float opacity = 1.0f;
	float currentOpacity = opacity;
	float opacityStep = 0.04f;

	const float scale = 3.0f;
	float currentScale = scale;
	float scaleStep = 0.1f;


	int time = CONFIG.getStartDelay_s()-1;
	int currentTime = time;
	bool isStarted = false;
	bool isTimerInitialized = false;

	Timer counterTimer;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoNav |
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove;

	void changeTimeCb();
	void setTextCenter(std::string text);
};