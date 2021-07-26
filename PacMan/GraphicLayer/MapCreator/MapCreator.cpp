#include "MapCreator.h"

void MapCreator::create(){
	
	ImageConcat mergeTool(MapManager::instance().getMapXSize(),
						  MapManager::instance().getMapYSize());
	MapMatchPattern patternTool;
	std::vector<MapPatternType> cellPatternData = patternTool.getMatch();

	for (auto& cellPat : cellPatternData) {
		mergeTool.addImage(imagePathMap[cellPat]);
	}
	mergeTool.convert();

}
