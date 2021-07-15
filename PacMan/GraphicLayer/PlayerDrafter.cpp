#include "PlayerDrafter.h"

void PlayerDrafter::draw(Position pos, Direction dir){
	normalize(pos);
	trans.setRotation(currentAngle);
	trans.setTranslation(pos.getX(), pos.getY());
	trans.setScale(0.1f);
	Render2D::instance().addToDraw(text, trans);

    trans.setRotation(-currentAngle);
	trans.setTranslation(pos.getX(), pos.getY());
	trans.setScale(0.1f);
	Render2D::instance().addToDraw(text, trans);

	currentAngle += rotationStep;
	if (currentAngle >= maxRotationAngle || currentAngle <= 0) rotationStep *= -1;

}
