
#include <iostream>
#include <iostream>

#include "Position.h"
#include "Movement.h"


int main() {

	Position pos{};
	Movement oper(1);

	oper.moveUp(pos);
	std::cout << pos <<std::endl;

	for (int i = 0; i < 10; i++) {
		oper.moveRight(pos);
		if (i == 5) oper.setStepSize(2);
		std::cout << pos << std::endl;
	}

	oper.moveLeft(pos);
	std::cout << pos << std::endl;

	oper.moveRight(pos);
	std::cout << pos << std::endl;

	oper.moveDown(pos);
	std::cout << pos << std::endl;





}