#include "Position.h"

void Position::move(Position& pos)
{
	x += pos.x;
	y += pos.y;
}

float Position::distance(Position& pos){
	float diff_x =  x - pos.x;
	float diff_y =  y - pos.y;
	return sqrtf(powf(diff_x, 2) + powf(diff_y, 2));
}

bool Position::operator==(Position& pos){
	return x == pos.x && y == pos.y;
}
