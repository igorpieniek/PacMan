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
    std::cout << " Pos center " << center << " X test" << (center.getX() == std::round(center.getX()) )
                                          << " Y test"<< (center.getY() == std::round(center.getY()) ) << std::endl;
    if ((std::round(center.getX()*1000)/1000 == std::round(center.getX()) &&
        std::round(center.getY() * 1000) / 1000 == std::round(center.getY()))) {
        std::cout << " Normalized position reached\n";
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

