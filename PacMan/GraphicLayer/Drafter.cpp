#include "Drafter.h"

float Drafter::scale = 0.0f;
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

	CoordType maxRealMapSize = std::max(MapManager::instance().getMapXSize(),
							            MapManager::instance().getMapYSize());

	constexpr float mainScale = 0.8f; // <0,1>

	constexpr float maxWindowWidth = 2.0f;
	constexpr float maxWidth = mainScale * maxWindowWidth;
	scale =  maxWidth / maxRealMapSize;
	float correctionRatio = ((MapManager::instance().getMapYSize()) / (MapManager::instance().getMapXSize()));
	
	if (correctionRatio > 1.0f) {
		correctionRatio = 1 / correctionRatio;
	}

	correctionRatio *= mainScale;


	if (MapManager::instance().getMapXSize() == maxRealMapSize) {
		correction = Position{ maxWidth/2 , correctionRatio };
	}
	else {
		correction = Position{ correctionRatio, maxWidth/2 };
	}
}

void Drafter::normalize(Position& pos) {
	pos = { (pos.getX() * scale) - correction.getX() + scale /2,
			(pos.getY() * scale) - correction.getY() + scale /2, };
}
