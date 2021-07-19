#include "CookieDrafter.h"

void CookieDrafter::draw(Position pos, Direction dir){
	normalize(pos);
	trans.setTranslation(pos.getX(), pos.getY());
	trans.setScale(0.02f);
	Render2D::instance().addToDraw(text, trans);
}
