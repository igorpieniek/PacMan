#include "MapManager.h"

MapManager::MapManager(Board& map){
	std::move(map.begin(), map.end(), mapBoard.begin());
}
