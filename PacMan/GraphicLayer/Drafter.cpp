#include "Drafter.h"

float Drafter::scale = 0.0f;
float Drafter::cellSize = 0.0f;
Position Drafter::correction = Position();

void Drafter::addImage(std::string path, Direction dir){
	filePath = path;
	imageOriginalDirection = dir;
	text = std::make_shared<Texture>(path);
	calculateScale();
}

void Drafter::draw(Position pos, Direction dir){
	normalize(pos);
	trans.setTranslation(pos.getX(), pos.getY());
	trans.setScale(0.08f);
	Render2D::instance().addToDraw(text, trans);
}

void Drafter::calculateScale() {
	if (scale != 0) return;
	CoordType max = std::max(MapManager::instance().getMapXSize(),
							 MapManager::instance().getMapYSize());
	cellSize = 2 / max;
	scale =  (2 - (2 * cellSize)) / (max-2);
	float correctionRatio = ((MapManager::instance().getMapYSize()) / (MapManager::instance().getMapXSize()));
	
	if (correctionRatio > 1.0f) {
		correctionRatio = 1 / correctionRatio;
	}


	if (MapManager::instance().getMapXSize() == max) {
		correction = Position{ 1.0f, correctionRatio };
	}
	else {
		correction = Position{ correctionRatio, 1.0f};
	}
}

void Drafter::normalize(Position& pos) {
	pos = { (pos.getX() * scale) - correction.getX() + cellSize/2, 
			(pos.getY() * scale) - correction.getY() + cellSize/2, };
}
