#include "PacManApp.h"
std::shared_ptr<PlayerMovement> PacManApp::playerMovement = std::make_shared<PlayerMovement>(1);

PacManApp::PacManApp(){
	MapManager::instance().addMap(CONFIG.getMapTxtPath());

	playerMovement = std::make_shared<PlayerMovement>(CONFIG.getPlayerSpeed());
	player = std::make_shared<Player>(CONFIG.getPlayerInitialPosition(), playerMovement);
	points  = std::make_shared<PointsManager>(CONFIG.getAmountOfSpecialPoints());
	opManag = std::make_shared<OponentManager>(CONFIG.getAmountOfOponents());


	if (!initGLFW())return;

	initImGui();

	graphManag = std::make_shared<GraphicGLManager>(points, player, opManag);
	gameRules = std::make_shared<GameRules>(std::vector<std::shared_ptr<GameMediatorComponent>>{ points, opManag, player, graphManag });
}


int PacManApp::process(){
	while (!glfwWindowShouldClose(window))
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		opManag->updateAll();
		player->update();
		Position playerPos = player->getPosition();
		gameRules->notifyPlayerPosition(playerPos);

		graphManag->draw();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}

bool PacManApp::initGLFW(){
	if (!glfwInit()) {
		std::cout << "Problem with glfw initialization" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(CONFIG.getMainWindowWidth(),
		CONFIG.getMainWindowHeight(),
		"PacMan", NULL, NULL);

	if (!window) {
		glfwTerminate();
		std::cout << "Glfw window terminate" << std::endl;
		return false;
	}

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{ playerMovement->keyActionCallback(window, key, scancode, action, mods); });

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);


	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW PROBLEM\n";
		return false;
	}
	return true;
}

void PacManApp::initImGui(){
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
}

