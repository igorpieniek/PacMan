#pragma once

#include "MapManager.h"
#include "MapMatchPattern.h"
#include <map>
#include <string>



class MapCreator{
public:
	void create();
private:
	std::map<MapPatternType, std::string> imagePathMap = {
		{MapPatternType::FREE , ""},
		{MapPatternType::VERTICAL , ""},
		{MapPatternType::HORIZONTAL , ""},
		{MapPatternType::CORNER_CONCAVE_NE , ""},
		{MapPatternType::CORNER_CONCAVE_SE , ""},
		{MapPatternType::CORNER_CONCAVE_NW , ""},
		{MapPatternType::CORNER_CONCAVE_SW , ""},
		{MapPatternType::CORNER_CONVEX_NE , ""},
		{MapPatternType::CORNER_CONVEX_NW , ""},
		{MapPatternType::CORNER_CONVEX_SE , ""},
		{MapPatternType::CORNER_CONVEX_SW , ""}
	};
};

