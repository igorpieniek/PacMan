#include "Drafter.h"


void Drafter::addImage(std::string path, Direction dir = Direction::EAST){
	filePath = path;
	imageOriginalDirection = dir;
	text = std::make_shared<Texture>(path);
}

void Drafter::draw(Position pos, Direction dir){
	trans.setTranslation(pos.getX(), pos.getY());
	trans.setScale(0.3f);
	Render2D::instance().addToDraw(text, trans);
}
