#include "StartMenu.h"

StartMenu::StartMenu(): SimpleMenu(450, 130){
	setMessages("Are you ready?","Yes","No");
}

bool StartMenu::drawAndGetStatus(){
	SimpleMenu::Answear answ = draw();
	if (answ == SimpleMenu::Answear::YES) {
		return true;
	}
	else if (answ == SimpleMenu::Answear::NO) {
		exit(0);
	}
	return false;
}

