#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"


#include "Position.h"
#include "MapManager.h"
#include "OponentManager.h"
#include "Player.h"
#include "PlayerMovement.h"
#include "GameRules.h"
#include "PointsManager.h"

#include "GraphicLayer/GraphicGLManager.h"

#include "ConfigLoader.h"


class PacManApp{
public:
	PacManApp();
	int process();
	~PacManApp();
private:
	static std::shared_ptr<PlayerMovement> playerMovement;
	std::shared_ptr<Player> player;
	std::shared_ptr<PointsManager> points;
	std::shared_ptr<OponentManager> opManag;
	std::shared_ptr<GraphicGLManager> graphManag;
	std::shared_ptr<GameRules> gameRules;

	GLFWwindow* window;

	bool initGLFW();
	void initImGui();
};

