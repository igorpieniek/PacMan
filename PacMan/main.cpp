
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include <windows.h>

#include <thread>

#include "Position.h"
#include "MapCell.h"
#include "MapManager.h"
#include "MoveAlgorithm.h"
#include "RandMove.h"
#include "Behaviour.h"

#include "OponentManager.h"
#include "Player.h"

#include "GameRules.h"
#include "PointsManager.h"


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77


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
		else if (pl.getPosition() == cell) {
			pl.draw();
		}
		else std::cout << "  ";

	}
	std::cout << std::endl;
}

static Player pl(Position{ 11,3 }, 1);

static void userInput_thread(void)
{
	while (true) {
		int key = std::getchar();
		switch (key){
		case 'w':
			std::cout << "up pressed\n";
			pl.moveDown();
			break;
		case 's':
			pl.moveUp();
			break;
		case 'a':
			std::cout << "left pressed\n";
			pl.moveLeft();
			break;
		case 'd':
			pl.moveRight();
			break;

		default:
			break;
		}
	}
}

static void app_thread(void) {
	MapManager::instance().addMap("mapa.txt");
	std::cout << "\n";

	

	PointsManager points{ 5 };
	OponentManager opManag{ 4 };


	GameRules gameRules({ &points, &opManag, &pl });

	while (true) {
		std::cout << "Player position = " << pl.getPosition() 
			      << ", lifes = " << pl.getAmountOfLifes() << std::endl;

		printAll(MapManager::instance().getAllMap(), &opManag, pl);

		opManag.updateAll();
		Position playerPos = pl.getPosition();
		gameRules.notifyPlayerPosition(playerPos);
		

		Sleep(500);
		system("CLS");
	}
}

int main() {

	std::thread thInput(userInput_thread);
	std::thread thApp(app_thread);

	thInput.join();
	thApp.join();
	

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