
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>

#include "Position.h"
#include "Movement.h"
#include "MapCell.h"
#include "MapManager.h"



void printMap(std::vector<MapCell>& mp) {
	int last = 0;
	for (auto cell : mp) {
		if (cell.getX() < last) std::cout << '\n';
		last = cell.getX();

		if (cell.isObstacle()) {
			std::cout << 'o';
		}
		else std::cout << '*';
		
	}
}

std::vector<MapCell> readMap(std::string file) {
	std::ifstream infile(file);
	std::string line;
	int lineNumber = 0;
	std::vector<MapCell> mp;
	while (std::getline(infile, line)) {
		for (auto i = 0; i < line.size(); i++) {
			if (line[i] == '1') {
				mp.push_back({ {lineNumber,i}, MapCell::Category::OBSTACLE });
			}
			else if (line[i] == '0') {
				mp.push_back({ {lineNumber,i}, MapCell::Category::FREE});
			}
		}
		lineNumber++;
	}

	return mp;
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


	const int boardSize = 10;
	std::vector<MapCell> mc;
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			if (x % 2) {
				mc.push_back({ {x,y} , MapCell::Category::FREE });
			}
			else {
				mc.push_back({ {x,y} , MapCell::Category::OBSTACLE });
			}
		}
	}
	printMap(mc);


	MapManager mapManager { mc };
	Position test{ 24,45 };
	std::vector<MapCell> nb = mapManager.getNeighbours(test, 1);
	std::cout << "\n";
	printMap(nb);



	std::vector<MapCell> res =  readMap("mapa.txt");
	std::cout << "\n";
	std::cout << "\n";
	printMap(res);


}