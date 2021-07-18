
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
#include "PlayerMovementManager.h"

#include "GameRules.h"
#include "PointsManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "GraphicLayer/GraphicGLManager.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>



std::shared_ptr<Player> pl = std::make_shared<Player>(Position{ 11.0f,3.f }, 0.1f);

void positionTest(GLFWwindow* window, int key, int scancode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_UP:
		pl->moveUp();
		break;
	case GLFW_KEY_DOWN:
		pl->moveDown();
		break;
	case GLFW_KEY_LEFT:
		pl->moveRight();
		break;
	case GLFW_KEY_RIGHT:
		pl->moveLeft();
		break;

	default:
		break;
	}

}

int main() {

	MapManager::instance().addMap("mapa.txt");

	PointsManager points{ 10 };
	std::shared_ptr<OponentManager> opManag = std::make_shared<OponentManager>( 2 );

	GameRules gameRules({ &points, opManag.get(), pl.get() });
	

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

	glfwSetKeyCallback(window, positionTest);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);


	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW PROBLEM\n";
	}

	GraphicGLManager graphManag(pl, opManag);
	

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		opManag->updateAll();
		Position playerPos = pl->getPosition();
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