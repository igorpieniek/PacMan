#include "PointCounter.h"

void PointCounter::setValue(int points){
	ImGui::SetNextWindowPos(ImVec2( Xpos, Ypos));
	ImGui::SetNextWindowSize(ImVec2(100, 50));
	ImGui::Begin("pointcounter", NULL, window_flags);    

	ImGui::SetWindowFontScale(scale);
	ImGui::Text(std::to_string(points).c_str());

	ImGui::End();

}
