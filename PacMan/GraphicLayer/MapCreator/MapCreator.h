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
	const std::string  newMapFile = ConfigLoader::instance().getDynamicMapImgPath();
	std::map<MapPatternType, std::string> imagePathMap = {
		{MapPatternType::FREE ,				 ConfigLoader::instance().getMapElementEmptyImgPath()},
		{MapPatternType::VERTICAL ,			 ConfigLoader::instance().getMapElementVerticalImgPath()},
		{MapPatternType::HORIZONTAL ,		 ConfigLoader::instance().getMapElementHorizontalImgPath()},
		{MapPatternType::CORNER_CONCAVE_NE , ConfigLoader::instance().getMapElementCornerNEImgPath()},
		{MapPatternType::CORNER_CONCAVE_SE , ConfigLoader::instance().getMapElementCornerSEImgPath()},
		{MapPatternType::CORNER_CONCAVE_NW , ConfigLoader::instance().getMapElementCornerNWImgPath()},
		{MapPatternType::CORNER_CONCAVE_SW , ConfigLoader::instance().getMapElementCornerSWImgPath()},
		{MapPatternType::CORNER_CONVEX_NE ,  ConfigLoader::instance().getMapElementCornerSWImgPath()},
		{MapPatternType::CORNER_CONVEX_NW ,  ConfigLoader::instance().getMapElementCornerSEImgPath()},
		{MapPatternType::CORNER_CONVEX_SE ,  ConfigLoader::instance().getMapElementCornerNWImgPath()},
		{MapPatternType::CORNER_CONVEX_SW ,  ConfigLoader::instance().getMapElementCornerNEImgPath()},
	};
};

