#include "StartMenu.h"

bool StartMenu::drawAndGetStatus(){
	bool status = false;
	ImGui::SetNextWindowPos(ImVec2(Xpos, Ypos));
	ImGui::SetNextWindowSize(ImVec2(Xsize, Ysize));
	ImGui::Begin("StartMenu", NULL, window_flags);
	ImGui::SetWindowFontScale(scale);

	std::string question = "Are you ready?";
	setTextCenter(question);
	ImGui::Text(question.c_str());

	ImGui::Dummy(ImVec2(0, 20));
	ImGui::BeginGroup();

	ImGui::Dummy(ImVec2(Xsize /4, 0));
	ImGui::SameLine();
	if (ImGui::Button("Yes"))
		status = true;

	ImGui::SameLine();
	ImGui::Dummy(ImVec2(Xsize / 4, 0));
	ImGui::SameLine();
	if (ImGui::Button("No"))
		exit(0);
	ImGui::EndGroup();
	ImGui::Dummy(ImVec2(0, 1));
	ImGui::End();
	return status;
}


void StartMenu::setTextCenter(std::string& text) {
	float font_size = ImGui::GetFontSize() * text.size() / 2;
	ImGui::SameLine(
		ImGui::GetWindowSize().x / 2 -
		font_size + (font_size / 2)
	);
}

