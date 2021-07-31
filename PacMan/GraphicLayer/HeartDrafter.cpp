#include "HeartDrafter.h"

void HeartDrafter::draw(Position pos, Direction dir){
	normalize(pos);
	trans.setTranslation(pos.getX(), pos.getY());
	trans.setScale(0.15f);


	Render2D::instance().addToDraw(text, trans);
}
