#include "CookieDrafter.h"

void CookieDrafter::draw(Position pos, Direction dir){
	normalize(pos);
	trans.setTranslation(pos.getX(), pos.getY());
	if (isSpecialPoint) {
		trans.setScale(3.0f*scale);
		isSpecialPoint = false;
	}
	else {
		trans.setScale(2.0f*scale);
	}
	Render2D::instance().addToDraw(text, trans);
}
