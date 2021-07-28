#include "RandMove.h"

void RandMove::update(Position& current){
    moveProcess(current);
    isInitialized = true;
}

void RandMove::setStepResolution(CoordType res){
    moveTool.setStepSize(res);
}

void RandMove::reset(){
    isInitialized = false;
}

void RandMove::moveProcess(Position& pos) {
    currentDirection = getBestDirection(pos);
    moveTool.moveInDir(pos, currentDirection);
}


Direction RandMove::getBestDirection(Position& center) {
    if (center.isIntPos()) {
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

void RandMove::deleteCurrentDirection(std::vector<Direction>& dir){
    auto iter = std::find(dir.begin(), dir.end(), getOpprositeDirection(currentDirection));
    if (iter != dir.end()) {
        dir.erase(iter);
    }
}

int RandMove::getRandomValue(int min, int max){
    return std::rand() % max + min;
}

