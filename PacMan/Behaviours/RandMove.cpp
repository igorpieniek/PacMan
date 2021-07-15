#include "RandMove.h"

Position RandMove::getNextPosition(Position& current){
    Position pos;
    pos = moveProcess(current);
    isInitialized = true;
    
    return pos;
}

void RandMove::setStepResolution(CoordType res){
    moveTool.setStepSize(res);
}


Position RandMove::moveProcess(Position& pos) {
    currentDirection = getBestDirection(pos);
    Position resultPos = pos;
    moveTool.moveInDir(resultPos, currentDirection);
    return resultPos;
}


Direction RandMove::getBestDirection(Position& center) {
    if (isIntPosition(center)) {
        std::vector<Direction> directions = MapManager::instance().getAllPossibleDirections(center);

        if (directions.size() == 1) return directions[0];


        if (isInitialized) {
            deleteCurrentDirection(directions);
        }

        int randIndex = getRandomValue(0, directions.size());
        return directions[randIndex];
    }
    else {
        return currentDirection;
    }
}

bool RandMove::isIntPosition(Position& pos){
    return (std::round(pos.getX() * 1000) / 1000 == std::round(pos.getX()) &&
            std::round(pos.getY() * 1000) / 1000 == std::round(pos.getY()));
}


void RandMove::deleteCurrentDirection(std::vector<Direction>& dir){
    auto iter = std::find(dir.begin(), dir.end(), getOpprositeDirection(currentDirection));
    if (iter != dir.end()) {
        dir.erase(iter);
    }
}

int RandMove::getRandomValue(int min, int max){
    return std::rand() % max + min;
}

