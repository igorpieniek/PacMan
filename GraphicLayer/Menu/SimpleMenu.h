#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#include "ConfigLoader.h"
#include <string>


class SimpleMenu{
protected:
	SimpleMenu(float w, float h);

	enum class Answear {
		NOTHING, YES, NO 
	};

	void setMessages(std::string quest, std::string y, std::string n);
	Answear draw();
	
	std::string extra;

private:
	const float scale = 2.0f;

	float Xsize{};
	float Ysize{};
	float Xpos{};
	float Ypos{};

	std::string question{}, yes{}, no{};

	ImGuiWindowFlags window_flags =
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoNav |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize;

	void setTextCenter(std::string& text);
};

