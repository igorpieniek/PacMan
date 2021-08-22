#include "HeartDrafter.h"

void HeartDrafter::draw(Position pos, Direction dir){
	for (int i = 0; i < currentNumberOfLives; i++) {
		Position current = pos + Position{ i * 3.0f ,0 };
		normalize( current );
		trans.setTranslation(current.getX(), current.getY() + 0.05f);
		trans.setScale(0.15f);
		Render2D::instance().addToDraw(text, trans);
	}
}

void HeartDrafter::setNumberOfLives(int lives){
	currentNumberOfLives = lives;
}
