#include "CookieDrafter.h"

void CookieDrafter::draw(Position pos, Direction dir){
	normalize(pos);
	trans.setTranslation(pos.getX(), pos.getY());
	if (isSpecialPoint) {
		trans.setScale(0.18f);
		isSpecialPoint = false;
	}
	else {
		trans.setScale(0.11f);
	}
	Render2D::instance().addToDraw(text, trans);
}
