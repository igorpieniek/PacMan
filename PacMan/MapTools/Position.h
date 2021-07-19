#pragma once

#ifndef __POSITION_H__
#define __POSITION_H__

#include <math.h>
#include <iostream>
#include <cmath>


using CoordType = float;

class Position{
public:

	Position(CoordType xx = { }, CoordType yy = {}) : x(xx), y(yy) {};

	void move(Position& pos);
	double distance(Position& pos);

	CoordType getX()const { return x; };
	CoordType getY()const { return y; };

	Position getIntPos() const;
	bool isIntPos()const;
	bool isXCoordInt()const;
	bool isYCoordInt()const;


	bool operator==(const Position& pos);
	Position operator+(const Position& pos);
	Position& operator+=(const Position& rPos);
	Position operator/(const CoordType& b) const;
	Position operator*(const CoordType& b) const;
	

private:
	CoordType x;
	CoordType y;
	friend std::ostream& operator<<(std::ostream& os, const Position& pos);
};



#endif // __POSITION_H__