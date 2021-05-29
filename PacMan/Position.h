#pragma once

#ifndef __POSITION_H__
#define __POSITION_H__

#include <math.h>


class Position{
public:
	Position(int xx = { }, int yy = {}) : x(xx), y(yy) {};

	void move(Position& pos);
	double distance(Position& pos);

	//bool operator==(Position& pos);
	bool operator==(const Position& pos);

private:
	int x;
	int y;
};



#endif // __POSITION_H__