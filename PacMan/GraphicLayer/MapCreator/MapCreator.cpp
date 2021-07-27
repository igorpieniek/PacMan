#include "MapCreator.h"

void MapCreator::create(){
	
	ImageConcat mergeTool(MapManager::instance().getMapXSize(),
						  MapManager::instance().getMapYSize(),
						  newMapFile );

	MapMatchPattern patternTool;
	std::vector<MapPatternType> cellPatternData = patternTool.getMatchForWholeMap();

	for (auto& cellPat : cellPatternData) {
		mergeTool.addImage(imagePathMap[cellPat]);
	}
	mergeTool.convert();

}

std::string MapCreator::getNewFileName() const{
	return newMapFile;
}
