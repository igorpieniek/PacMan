#pragma once

#include <string>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#include "ConfigLoader.h"

class PointCounter{
public:
	void setValue(int points);

private:
	const float scale = 3.0f;
	const float Xpos = 0.8f *  CONFIG.getMainWindowWidth();
	const float Ypos = 0.02f * CONFIG.getMainWindowHeight();


	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar |
									ImGuiWindowFlags_NoScrollbar|
									ImGuiWindowFlags_NoCollapse|
									ImGuiWindowFlags_NoNav|
									ImGuiWindowFlags_NoBackground|
									ImGuiWindowFlags_NoDecoration|
									ImGuiWindowFlags_NoMove;
};

