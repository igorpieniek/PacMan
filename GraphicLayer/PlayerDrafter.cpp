#include "PlayerDrafter.h"

void PlayerDrafter::draw(Position pos, Direction dir){
	normalize(pos);
	const float playerScale = 1.5f * scale;
	trans.setRotation(currentAngle + rotations[dir]);
	trans.setTranslation(pos.getX(), pos.getY());
	trans.setScale(playerScale);
	Render2D::instance().addToDraw(text, trans);

    trans.setRotation(-currentAngle + rotations[dir]);
	trans.setTranslation(pos.getX(), pos.getY());
	trans.setScale(playerScale);
	Render2D::instance().addToDraw(text, trans);
	
	if (isMoving) {
		currentAngle += rotationStep;
		if (currentAngle >= maxRotationAngle || currentAngle <= 0) rotationStep *= -1;
	}
}

void PlayerDrafter::updateIsMoving(bool movingFlag){
	isMoving = movingFlag;
}
