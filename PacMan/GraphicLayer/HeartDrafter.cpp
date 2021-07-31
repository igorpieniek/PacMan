#include "HeartDrafter.h"

void HeartDrafter::draw(Position pos, Direction dir){
	normalize(pos);
	trans.setTranslation(pos.getX(), pos.getY());
	trans.setScale(0.2f);


	Render2D::instance().addToDraw(text, trans);
}
