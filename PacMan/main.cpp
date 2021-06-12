
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include <windows.h>

#include "Position.h"
#include "MapCell.h"
#include "MapManager.h"
#include "MoveAlgorithm.h"
#include "RandMove.h"
#include "Behaviour.h"

#include "OponentManager.h"
#include "Player.h"





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
		else std::cout << "  ";
		
	}
}

void printAll(std::vector<MapCell>& mp, OponentManager* op, Player& pl) {
	int last = 0;
	for (auto cell : mp) {
		if (cell.getX() < last) std::cout << '\n';
		last = cell.getX();

		if (cell.isObstacle()) {
			std::cout << " o";
		}
		else if (op->isOponentsAndDraw(cell)){}
		/*else if (pl.getPosition() == cell) {
			pl.draw();
		}*/
		else std::cout << "  ";

	}
}



int main() {

	MapManager::instance().addMap("mapa.txt");
	std::cout << "\n";
	
	OponentManager opManag{ 4 };
	Player pl(Position{ 1,2 }, 1);

	
	for (int i = 0; i < 250; i++) {
		printAll(MapManager::instance().getAllMap(), &opManag, pl);

		opManag.updateAll();
		//pl.update();

		Sleep(70);
		system("CLS");
	}

	/*
	Position p{ 1,2 };
	for (int i = 0; i < 40; i++) {
		std::cout << p << std::endl;
		printMap(res.getAllMap(), &p);
		p = rm.getNextPosition(p);
		Sleep(400);
		system("CLS");
	}
	
	
	std::cout << "\n";
	for (auto c : cp) {
		if (mapManager2.isCorner(c)) {
			std::cout << "Corner found for point " << c << std::endl;
		}
	}

	*/


}