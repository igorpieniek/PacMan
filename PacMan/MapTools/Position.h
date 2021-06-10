#pragma once

#ifndef __POSITION_H__
#define __POSITION_H__

#include <math.h>
#include <iostream>


class Position{
public:
	Position(int xx = { }, int yy = {}) : x(xx), y(yy) {};

	void move(Position& pos);
	double distance(Position& pos);

	int getX()const { return x; };
	int getY()const { return y; };

	bool operator==(const Position& pos);
	Position operator+(const Position& pos);
	Position& operator+=(const Position& rPos);
	

private:
	int x;
	int y;
	friend std::ostream& operator<<(std::ostream& os, const Position& pos);
};



#endif // __POSITION_H__