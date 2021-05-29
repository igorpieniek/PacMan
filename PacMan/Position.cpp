#include "Position.h"

void Position::move(Position& pos)
{
	x += pos.x;
	y += pos.y;
}

double Position::distance(Position& pos){
	return sqrt(pow(x - pos.x, 2) + pow(y - pos.y, 2));
}

bool Position::operator==(Position& pos){
	return x == pos.x && y == pos.y;
}
