#include "RandMove.h"

void RandMove::update(Position& current){
    moveProcess(current);
}

void RandMove::setStepResolution(CoordType res){
    if (res < 0.0f || res > 1.0f) {
        throw std::runtime_error("RandMove: speed must be from range <0,1> your value: " + std::to_string(res));
    }
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
    if (center.isIntPos() || !isInitialized) {
        std::vector<Direction> directions = getAllPossibleDirecions(center);//MapManager::instance().getAllPossibleDirections(center);

        if (directions.size() == 1) return directions[0];

        if (isInitialized) {
            deleteCurrentDirection(directions);
        }
        else {
            isInitialized = true;
        }

        int randIndex = getRandomValue(0, directions.size()-1);
        return directions[randIndex];
    }
    else {
        return currentDirection;
    }
}

std::vector<Direction> RandMove::getAllPossibleDirecions(const Position& pos){
    std::vector<Direction> res;
    res.reserve(4);
    for (const auto& dir : allDirections) {
        if (moveTool.isNextPositionFree(pos, dir)) {
            res.push_back(dir);
        }
    }
    return std::move(res);
}

void RandMove::deleteCurrentDirection(std::vector<Direction>& dir){
    auto iter = std::find(dir.begin(), dir.end(), getOpprositeDirection(currentDirection));
    if (iter != dir.end()) {
        dir.erase(iter);
    }
}

int RandMove::getRandomValue(int min, int max){
    std::uniform_int_distribution<> randomizer(min, max);
    return randomizer(generator);
}

