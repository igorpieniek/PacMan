#pragma once
#include "GraphicManagerInterface.h"
class GraphicGLManager :public GraphicManagerInterface{
public:
	GraphicGLManager(const std::shared_ptr<Player> pl,
					 const std::shared_ptr<OponentManager> oponentManag);

	void draw() override;
private:
};

