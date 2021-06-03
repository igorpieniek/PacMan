#include "RandMove.h"

Position RandMove::getNextPosition(Position& current){
    Position pos;
    if (isInitialized) {
        pos = normalMoveProcess(current);
    }
    else {
        isInitialized = false;
        pos = firstMoveProcess(current);
    }
    return pos;
}

int RandMove::getRandomValue(int min, int max){
    return std::rand() % max + min;
}

Position RandMove::getPositionInDirection(Position& center, Direction dir){
    Position newPos = center;
    moveTool.moveInDir(newPos, dir);
    return newPos;
}

Direction RandMove::getBestDirection(Position& center){
    std::vector<Direction> directions = mapManager->getAllPossibleDirections(center);
    if (directions.size() == 1) return directions[0];

    auto iter = std::find(directions.begin(), directions.end(), currentDirection);
    if (iter != directions.end()) {
        directions.erase(iter);
    }
    
    directions.erase(std::remove(directions.begin(), directions.end(), currentDirection), 
                     directions.end());

    if (directions.size() == 1) return directions[0];

    int randIndex = getRandomValue(0, directions.size());
    return directions[randIndex];
}

Position RandMove::firstMoveProcess(Position& pos){
    int randIndex = getRandomValue(0, 3);
    currentDirection = static_cast<Direction>(randIndex);
    Direction dir = getBestDirection(pos);
    Position resultPos = pos;
    moveTool.moveInDir(resultPos, dir);
    return resultPos;
}

Position RandMove::normalMoveProcess(Position& pos){
    Position checkPos = getPositionInDirection(pos, currentDirection);
    if (mapManager->isOccupied(checkPos)){ 
        currentDirection = getBestDirection(pos);
        checkPos = pos;
        moveTool.moveInDir(checkPos, currentDirection);
    }
    return checkPos;
}
