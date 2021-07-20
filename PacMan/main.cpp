#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Position.h"
#include "MapManager.h"
#include "OponentManager.h"
#include "Player.h"
#include "GameRules.h"
#include "PointsManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "GraphicLayer/GraphicGLManager.h"
#include "PlayerMovementManager.h"


std::shared_ptr<Player> pl = std::make_shared<Player>(Position{ 1.0f,1.f }, 0.1f);
PlayerMovementManager playerMovement(pl);


int main() {

	MapManager::instance().addMap("mapa.txt");

	std::shared_ptr<PointsManager> points = std::make_shared<PointsManager>( 10 );
	std::shared_ptr<OponentManager> opManag = std::make_shared<OponentManager>( 4 );
	

	GameRules gameRules({ points.get(), opManag.get(), pl.get() });

	
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


	//glfwSetKeyCallback(window, positionTest);
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
							{ playerMovement.keyActionCallback(window, key, scancode, action, mods); });

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);


	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW PROBLEM\n";
	}

	GraphicGLManager graphManag(points, pl, opManag);
	

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		opManag->updateAll();
		Position playerPos = pl->getPosition();
		gameRules.notifyPlayerPosition(playerPos);

		playerMovement.update();

		graphManag.draw();


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}