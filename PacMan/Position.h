#pragma once

#ifndef __POSITION_H__
#define __POSITION_H__

#include <math.h>




class Position
{
public:
	Position(float xx = { }, float yy = {}) : x(xx), y(yy) {};

	void move(Position& pos);
	float distance(Position& pos);

	bool operator==(Position& pos);


private:
	float x;
	float y;
};



#endif // __POSITION_H__