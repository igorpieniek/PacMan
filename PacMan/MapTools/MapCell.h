#pragma once

#ifndef __MAPCELL_H__
#define __MAPCELL_H__


#include "Position.h"
class MapCell :public Position{
public:
	using Position::operator==;
	enum class Category {
		FREE,
		OBSTACLE
	};

	MapCell() = default;
	MapCell(Position pos, Category cat) : Position(pos), category(cat){};

	bool isObstacle() const;

private:
	Category category;
	using Position::move; //hiding method
};

#endif //__MAPCELL_H__