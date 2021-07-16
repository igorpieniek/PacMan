
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include <windows.h>

#include <thread>
#include <conio.h>

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
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "GraphicLayer/GraphicGLManager.h"



#include <GL/glew.h>
#include <GLFW/glfw3.h>


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77



void printAll(std::vector<MapCell>& mp, OponentManager* op, Player& pl, PointsManager& points) {
	CoordType last = 0;
	for (auto cell : mp) {
		if (cell.getX() < last) std::cout << '\n';
		last = cell.getX();

		PointCat cat;

		if (cell.isObstacle()) {
			std::cout << " o";
		}		
		else if (pl.getPosition() == cell) {
			//pl.draw();
		}
		else if (op->isOponentsAndDraw(cell)) {}
		else if (points.getPointCat(&cat, cell)) {
			if (cat == PointCat::NORMAL) {
				std::cout << " .";
			}
			else { //special
				std::cout << " ,";
			}
		}
		else std::cout << "  ";

	}
	std::cout << std::endl;
}

//static Player pl(Position{ 11,3 }, 1);
static Player pl(Position{ 11.0f,3.f }, 1);
static bool movePermission = true;

static void userInput_thread(void)
{
	while (true) {
		if (movePermission) {
			movePermission = false;
			int key = _getch();
			switch (key) {
			case KEY_UP:
				pl.moveDown();
				break;
			case KEY_DOWN:
				pl.moveUp();
				break;
			case KEY_LEFT:
				pl.moveRight();
				break;
			case KEY_RIGHT:
				pl.moveLeft();
				break;

			default:
				break;
			}
		}
	}
}

static void app_thread(void) {
	MapManager::instance().addMap("mapa.txt");
	std::cout << "\n";

	PointsManager points{ 10 };
	OponentManager opManag{ 4 };

	GameRules gameRules({ &points, &opManag, &pl });

	while (true) {
		movePermission = true;
		std::cout << "Player position = " << pl.getPosition() 
			      << ", lifes = " << pl.getAmountOfLifes()
				  << ", points = "<< points.getPoints()  <<std::endl;

		printAll(MapManager::instance().getAllMap(), &opManag, pl, points);
		opManag.updateAll();
		Position playerPos = pl.getPosition();
		gameRules.notifyPlayerPosition(playerPos);
		
		
		Sleep(50);
		system("CLS");
	}
}

int main() {

	//std::thread thInput(userInput_thread);
	//std::thread thApp(app_thread);

	//thInput.join();
	//thApp.join();

	MapManager::instance().addMap("mapa.txt");
	std::cout << "\n";

	PointsManager points{ 10 };
	std::shared_ptr<OponentManager> opManag = std::make_shared<OponentManager>( 2 );

	GameRules gameRules({ &points, opManag.get(), &pl });
	

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 640, "PacMan", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}



	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);


	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW PROBLEM\n";
	}

	GraphicGLManager graphManag(std::make_shared<Player>(pl), opManag);
	

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		opManag->updateAll();
		Position playerPos = pl.getPosition();
		gameRules.notifyPlayerPosition(playerPos);

		graphManag.draw();


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}