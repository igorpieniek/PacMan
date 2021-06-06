
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include <windows.h>

#include "Position.h"
#include "Movement.h"
#include "MapCell.h"
#include "MapManager.h"
#include "RandMove.h"
#include "Behaviour.h"
#include "Oponent.h"



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

void printAll(std::vector<MapCell>& mp, std::vector<Oponent>& ops) {
	int last = 0;
	for (auto cell : mp) {
		if (cell.getX() < last) std::cout << '\n';
		last = cell.getX();

		auto pred = [&cell](const Oponent& oponent) {return oponent.getPosition() == cell; };
		auto iter = find_if(ops.begin(), ops.end(), pred);

		if (cell.isObstacle()) {
			std::cout << " o";
		}
		else if (iter != ops.end()) {
			iter->draw();
		}
		else std::cout << "  ";

	}
}




int main() {

	MapManager res("mapa.txt");
	std::cout << "\n";

	RandMove rm(&res);
	Behaviour beh{ &rm };

	RandMove rm2(&res);
	Behaviour beh2{ &rm2 };

	RandMove rm3(&res);
	Behaviour beh3{ &rm3 };

	std::vector<Oponent> ops = {
		Oponent(Position{1,2}, &beh, 1, "g"),
		Oponent(Position{7,1}, &beh2, 1, "@"),
		Oponent(Position{8,6}, &beh3, 1, "D")
	};

	
	
	for (int i = 0; i < 200; i++) {
		printAll(res.getAllMap(), ops);
		for (auto& oponent : ops) {
			oponent.update();
		}

		Sleep(70);
		system("CLS");
	}

	/*
	* Position p{ 1,2 };
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