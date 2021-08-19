#include "FinishMenu.h"

FinishMenu::FinishMenu():SimpleMenu(450, 160) {
	setMessages("Do you want to play again?", "Yes", "No");
}

bool FinishMenu::drawAndGetStatus(bool isAll, int val){

	if (isAll) {
		extra = "You won! You get: " + std::to_string(val) + " pts";
	}
	else {
		extra = "You lose! You get: " + std::to_string(val) + " pts";
	}

	SimpleMenu::Answear answ = draw();
	if (answ == SimpleMenu::Answear::YES) {
		return true;
	}
	else if (answ == SimpleMenu::Answear::NO) {
		exit(0);
	}
	return false;
}
