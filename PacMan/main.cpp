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
#include "stb_image/stb_image.h"

#include "GraphicLayer/GraphicGLManager.h"
#include "PlayerMovement.h"

#include "ConfigLoader.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"



std::shared_ptr<PlayerMovement> playerMovement = std::make_shared<PlayerMovement>(CONFIG.getPlayerSpeed());
std::shared_ptr<Player> pl = std::make_shared<Player>(CONFIG.getPlayerInitialPosition(), playerMovement);



int main() {


	MapManager::instance().addMap(CONFIG.getMapTxtPath());

	std::shared_ptr<PointsManager> points = 
						std::make_shared<PointsManager>(CONFIG.getAmountOfSpecialPoints());
	std::shared_ptr<OponentManager> opManag =
						std::make_shared<OponentManager>(CONFIG.getAmountOfOponents());
	

	

	
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(CONFIG.getMainWindowWidth(),
							  CONFIG.getMainWindowHeight(),
							  "PacMan", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}


	//glfwSetKeyCallback(window, positionTest);
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
							{ playerMovement->keyActionCallback(window, key, scancode, action, mods); });

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);


	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW PROBLEM\n";
	}

	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");



	std::shared_ptr<GraphicGLManager> graphManag 
						= std::make_shared<GraphicGLManager>(points, pl, opManag);
	GameRules gameRules({ points, opManag, pl, graphManag });

	bool demoWindow = true;
	ImGuiWindowFlags window_flags = 0;
	 window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	//window_flags |= ImGuiWindowFlags_MenuBar;
	//window_flags |= ImGuiWindowFlags_NoMove;
	 //window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoNav;
	window_flags |= ImGuiWindowFlags_NoBackground;
	window_flags |= ImGuiWindowFlags_NoDecoration;
	//if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	//if (no_close)           p_open = NULL; // Don't pass our bool* to Begin


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (demoWindow) {
			ImGui::ShowDemoWindow(&demoWindow);
		}
		/*
		ImGui::Begin("window", NULL, window_flags);                          // Create a window called "Hello, world!" and append into it.

		

		ImGui::SetNextWindowPos(ImVec2(0.8*CONFIG.getMainWindowWidth(), 0.95*CONFIG.getMainWindowHeight()), ImGuiCond_FirstUseEver);
		ImGui::SetWindowFontScale(3.f);
		ImGui::Text(std::to_string(points->getPoints()).c_str() );
	
		ImGui::End();
		*/
		ImGui::Begin(" ", NULL, ImGuiWindowFlags_NoTitleBar | 
								ImGuiWindowFlags_MenuBar | 
								ImGuiWindowFlags_NoNav | 
								ImGuiWindowFlags_NoCollapse|
			ImGuiWindowFlags_NoDecoration);
		ImGui::SetWindowFontScale(2.f);
		ImGui::Text("Are you ready?");
		ImGui::BeginGroup();
		if( ImGui::Button("Yes") )
			std::cout << "Button clicked" << std::endl;
		ImGui::SameLine();
		if (ImGui::Button("No, close window"))
			exit(0);
		ImGui::EndGroup();
		ImGui::End();
		
		opManag->updateAll();
		pl->update();
		Position playerPos = pl->getPosition();
		gameRules.notifyPlayerPosition(playerPos);

		graphManag->draw();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;

}