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
	const float initOpacity = 100.0f;
	const float Xsize = 400;
	const float Ysize = 400;
	const float Xpos = 0.5f * CONFIG.getMainWindowWidth() - 0.5 * Xsize;
	const float Ypos = 0.5f * CONFIG.getMainWindowHeight() - 0.5 * Ysize;

	int time = CONFIG.getStartDelay_s();
	int currentTime = time;
	bool isStarted = false;
	bool isTimerInitialized = false;


	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoNav |
		ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove;

	void changeTimeCb();
};