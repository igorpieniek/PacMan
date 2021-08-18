#include "StartMenu.h"

bool StartMenu::drawAndGetStatus(){
	bool status = false;
	ImGui::SetNextWindowPos(ImVec2(Xpos, Ypos));
	ImGui::SetNextWindowSize(ImVec2(Xsize, Ysize));
	ImGui::Begin("StartMenu", NULL, window_flags);
	ImGui::SetWindowFontScale(scale);
	ImGui::Text("Are you ready?");
	ImGui::BeginGroup();
	if (ImGui::Button("Yes"))
		status = true;
	ImGui::SameLine();
	if (ImGui::Button("No, close window"))
		exit(0);
	ImGui::EndGroup();
	ImGui::End();
	return status;
}


