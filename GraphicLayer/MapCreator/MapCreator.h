#pragma once

#include "MapManager.h"
#include "MapMatchPattern.h"
#include "ImageConcat.h"
#include <map>
#include <string>
#include "ConfigLoader.h"


class MapCreator{
public:
	void create();
	std::string getNewFileName()const;
private:
	void imagePathExistCheck();
	const std::string  newMapFile = CONFIG.getDynamicMapImgPath();
	std::map<MapPatternType, std::string> imagePathMap = {
		{MapPatternType::FREE ,				 CONFIG.getMapElementEmptyImgPath()},
		{MapPatternType::VERTICAL ,			 CONFIG.getMapElementVerticalImgPath()},
		{MapPatternType::HORIZONTAL ,		 CONFIG.getMapElementHorizontalImgPath()},
		{MapPatternType::CORNER_CONCAVE_NE , CONFIG.getMapElementCornerNEImgPath()},
		{MapPatternType::CORNER_CONCAVE_SE , CONFIG.getMapElementCornerSEImgPath()},
		{MapPatternType::CORNER_CONCAVE_NW , CONFIG.getMapElementCornerNWImgPath()},
		{MapPatternType::CORNER_CONCAVE_SW , CONFIG.getMapElementCornerSWImgPath()},
		{MapPatternType::CORNER_CONVEX_NE ,  CONFIG.getMapElementCornerSWImgPath()},
		{MapPatternType::CORNER_CONVEX_NW ,  CONFIG.getMapElementCornerSEImgPath()},
		{MapPatternType::CORNER_CONVEX_SE ,  CONFIG.getMapElementCornerNWImgPath()},
		{MapPatternType::CORNER_CONVEX_SW ,  CONFIG.getMapElementCornerNEImgPath()},
	};
};

