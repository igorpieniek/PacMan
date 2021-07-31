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

	CoordType Xsize = MapManager::instance().getMapXSize();
	CoordType Ysize = MapManager::instance().getMapYSize();
	CoordType maxRealMapSize;
	float correctionRatio;
	float mainScale = 0.93f; // <0,1>
	constexpr float maxWindowWidth = 2.0f;
	if(Ysize >= Xsize){
		maxRealMapSize = Ysize;
		mainScale = 0.8f;
		correctionRatio = Xsize / Ysize;
	}
	else {
		maxRealMapSize = Xsize;
		correctionRatio = Ysize / Xsize;
	}

	const float maxWidth = mainScale * maxWindowWidth;
	scale =  maxWidth / maxRealMapSize;

	correctionRatio *= mainScale;

	if (Xsize >= Ysize) {
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
