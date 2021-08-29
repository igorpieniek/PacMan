#include "MapCreator.h"


void MapCreator::create(){
	
	imagePathExistCheck();

	ImageConcat mergeTool(static_cast<int>(MapManager::instance().getMapXSize()),
						  static_cast<int>(MapManager::instance().getMapYSize()),
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

void MapCreator::imagePathExistCheck(){
	for (const auto& path : imagePathMap) {
		if (FILE* file = fopen(path.second.c_str(), "r")) {
			fclose(file);
		}
		else {
			throw std::runtime_error("MapCreator: cannot open file " + path.second);
		}
	}
}
