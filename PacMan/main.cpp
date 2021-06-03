
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>

#include <windows.h>

#include "Position.h"
#include "Movement.h"
#include "MapCell.h"
#include "MapManager.h"
#include "RandMove.h"



void printMap(std::vector<MapCell>& mp , Position* pos) {
	int last = 0;
	for (auto cell : mp) {
		if (cell.getX() < last) std::cout << '\n';
		last = cell.getX();

		if (cell.isObstacle()) {
			std::cout << " o";
		}
		else if (pos != NULL && *pos == cell) {
			std::cout << " +";
		}
		else std::cout << " .";
		
	}
}




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



	MapManager res("mapa.txt");
	std::cout << "\n";

	RandMove rm(&res);

	Position p{ 1,2 };
	
	for (int i = 0; i < 40; i++) {
		std::cout << p << std::endl;
		printMap(res.getAllMap(), &p);
		p = rm.getNextPosition(p);
		Sleep(400);
		system("CLS");
	}
	
	/*
	std::cout << "\n";
	for (auto c : cp) {
		if (mapManager2.isCorner(c)) {
			std::cout << "Corner found for point " << c << std::endl;
		}
	}

	*/


}