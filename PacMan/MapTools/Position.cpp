#include "Position.h"
#include <iostream>


void Position::move(Position& pos){
	x += pos.x;
	y += pos.y;
}

double Position::distance(Position& pos){
	return sqrt(pow(x - pos.x, 2) + pow(y - pos.y, 2));
}

bool Position::operator==(const Position& pos){
	return this->x == pos.x && this->y == pos.y;
}

Position Position::operator+(const Position& pos){
	return Position(x + pos.x, y + pos.y);
}

Position& Position::operator+=(const Position& rPos){
	*this = operator+(rPos);
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Position& pos){
	return os << "(" << pos.x << ", " << pos.y << ")";
}
