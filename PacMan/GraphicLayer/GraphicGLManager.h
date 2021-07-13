#pragma once
#include "GraphicManagerInterface.h"
#include "Render2D.h"
#include "Drafter.h"
#include "MapManager.h"

#include <algorithm>

class GraphicGLManager :public GraphicManagerInterface{
public:
	GraphicGLManager(const std::shared_ptr<Player> pl,
					 const std::shared_ptr<OponentManager> oponentManag);

	void draw() override;
private:

	std::vector<Drafter> ghosts;
	float scale;

	void calculateScale();
	CoordType getNormalized(CoordType cord);
};

