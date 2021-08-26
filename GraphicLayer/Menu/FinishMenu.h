#pragma once

#include "Menu/SimpleMenu.h"


class FinishMenu : public SimpleMenu {
public:
	FinishMenu();
	bool drawAndGetStatus(bool isAll, int val);
};


