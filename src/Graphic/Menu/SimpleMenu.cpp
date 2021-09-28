#include "SimpleMenu.h"

SimpleMenu::SimpleMenu(float w, float h): Xsize(w), Ysize(h){
	Xpos = 0.5f * CONFIG.getMainWindowWidth()  - 0.5f * Xsize;
	Ypos = 0.5f * CONFIG.getMainWindowHeight() - 0.5f * Ysize;
}

void SimpleMenu::setMessages(std::string quest, std::string y, std::string n){
	question = quest;
	yes = y;
	no = n;
}

SimpleMenu::Answear SimpleMenu::draw(){
	Answear answ = Answear::NOTHING;
	ImGui::SetNextWindowPos(ImVec2(Xpos, Ypos));
	ImGui::SetNextWindowSize(ImVec2(Xsize, Ysize));
	ImGui::Begin(std::string("StartMenu"+question).c_str(), NULL, window_flags);
	ImGui::SetWindowFontScale(scale);

	if (extra.size() !=0) {
		setTextCenter(extra);
		ImGui::Text(extra.c_str());

		ImGui::Dummy(ImVec2(0, 20));
	}
	setTextCenter(question);
	ImGui::Text(question.c_str());

	ImGui::Dummy(ImVec2(0, 20));
	ImGui::BeginGroup();

	ImGui::Dummy(ImVec2(Xsize / 4.5f, 0));
	ImGui::SameLine();
	if (ImGui::Button(yes.c_str()))
		answ = Answear::YES;

	ImGui::SameLine();
	ImGui::Dummy(ImVec2(Xsize / 4, 0));
	ImGui::SameLine();
	if (ImGui::Button(no.c_str()))
		answ = Answear::NO;
	ImGui::EndGroup();
	ImGui::Dummy(ImVec2(0, 1));
	ImGui::End();

	return answ;
}



void SimpleMenu::setTextCenter(std::string& text) {
	float font_size = ImGui::GetFontSize() * text.size() / 2;
	ImGui::SameLine(
		ImGui::GetWindowSize().x / 2 -
		font_size + (font_size / 2)
	);
}
