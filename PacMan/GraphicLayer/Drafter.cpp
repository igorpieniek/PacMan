#include "Drafter.h"

float Drafter::scale = 0.0f;

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
	scale = 2 / max;
}

void Drafter::normalize(Position& pos) {
	pos = { (pos.getX() * scale) - 1.0f,
			(pos.getY() * scale) - 1.0f };
}
