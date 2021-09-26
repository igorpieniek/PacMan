#include "Position.h"
#include <iostream>


void Position::move(Position& pos){
	x += pos.x;
	y += pos.y;
}

double Position::distance(Position& pos)const {
	return sqrt(pow(x - pos.x, 2) + pow(y - pos.y, 2));
}

Position Position::getIntPos() const{
	return { std::round(x), std::round(y) };
}

bool Position::isIntPos() const{
	return isXCoordInt() && isYCoordInt();
}

bool Position::isXCoordInt() const{
	return std::round(x * 1000) / 1000 == getIntPos().getX();
}

bool Position::isYCoordInt() const{
	return std::round(y * 1000) / 1000 == getIntPos().getY();
}


bool Position::operator==(const Position& pos){
	return	   std::abs(this->x - pos.x) < ZERO_MARGIN_VAL
		    && std::abs(this->y - pos.y) < ZERO_MARGIN_VAL;
}

bool Position::operator!=(const Position& pos) {
	return !(*this == pos);
}

Position Position::operator+(const Position& pos){
	return Position(x + pos.x, y + pos.y);
}

Position& Position::operator+=(const Position& rPos){
	*this = operator+(rPos);
	return *this;
}

Position Position::operator/(const CoordType& b) const{
	return { x / b, y / b };
}

Position Position::operator*(const CoordType& b) const{
	return {x*b, y*b};
}

std::ostream& operator<<(std::ostream& os, const Position& pos){
	return os << "(" << pos.x << ", " << pos.y << ")";
}
