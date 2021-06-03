#include "RandMove.h"

Position RandMove::getNextPosition(Position& current){
    Position pos;
    pos = moveProcess(current);
    isInitialized = true;
    
    return pos;
}


Position RandMove::moveProcess(Position& pos) {
    currentDirection = getBestDirection(pos);
    Position resultPos = pos;
    moveTool.moveInDir(resultPos, currentDirection);
    return resultPos;
}

Direction RandMove::getBestDirection(Position& center) {
    std::vector<Direction> directions = mapManager->getAllPossibleDirections(center);

    if (directions.size() == 1) return directions[0];

    if (isInitialized) {
        deleteCurrentDirection(directions);
    }

    int randIndex = getRandomValue(0, directions.size());
    return directions[randIndex];
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

