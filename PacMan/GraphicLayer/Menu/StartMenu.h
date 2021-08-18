#pragma once

#include <string>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#include "ConfigLoader.h"

class StartMenu {
public:
	bool drawAndGetStatus();
private:
	const float scale = 2.0f;
	const float Xsize = 450;
	const float Ysize = 130;
	const float Xpos = 0.5f * CONFIG.getMainWindowWidth() - 0.5* Xsize;
	const float Ypos = 0.5f * CONFIG.getMainWindowHeight() - 0.5*Ysize;
	ImGuiWindowFlags window_flags =
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_MenuBar |
		ImGuiWindowFlags_NoNav |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove|
		ImGuiWindowFlags_NoResize;


};

