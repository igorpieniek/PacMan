#pragma once

#include "MapManager.h"
#include "MapMatchPattern.h"
#include "ImageConcat.h"
#include <map>
#include <string>



class MapCreator{
public:
	void create();
private:
	std::map<MapPatternType, std::string> imagePathMap = {
		{MapPatternType::FREE ,				 "images/empty.png"},
		{MapPatternType::VERTICAL ,			 "images/vertical.png"},
		{MapPatternType::HORIZONTAL ,		 "images/horizontal.png"},
		{MapPatternType::CORNER_CONCAVE_NE , "images/corner_NE.png"},
		{MapPatternType::CORNER_CONCAVE_SE , "images/corner_SE.png"},
		{MapPatternType::CORNER_CONCAVE_NW , "images/corner_NW.png"},
		{MapPatternType::CORNER_CONCAVE_SW , "images/corner_SW.png"},
		{MapPatternType::CORNER_CONVEX_NE ,  "images/corner_SW.png"},
		{MapPatternType::CORNER_CONVEX_NW ,  "images/corner_SE.png"},
		{MapPatternType::CORNER_CONVEX_SE ,  "images/corner_NW.png"},
		{MapPatternType::CORNER_CONVEX_SW ,  "images/corner_NE.png"},
	};
};

