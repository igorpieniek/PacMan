#include "RandMove.h"

Position RandMove::getNextPosition(Position& current){
    Position pos;
    if (isInitialized) {
        //pos = normalMoveProcess(current);
        pos = firstMoveProcess(current);
    }
    else {
        pos = firstMoveProcess(current);
        isInitialized = true;
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

Direction RandMove::getBestDirection(Position& center) {
    std::vector<Direction> directions = mapManager->getAllPossibleDirections(center);
    std::cout << '\n'<< center;
    for (auto const dir : directions) {
        printDirection(dir);
        std::cout << " ";
    }
    printDirection(currentDirection);
    std::cout << std::endl;

    if (directions.size() == 1) return directions[0];

    if (isInitialized) {
        std::cout << '\n' << center;
        auto iter = std::find(directions.begin(), directions.end(), getOpprositeDirection(currentDirection));
        if (iter != directions.end()) {
            std::cout << "Direction deleted "<<static_cast<int>(*iter) << '\n';
            directions.erase(iter);
        }
    }
    

    if (directions.size() == 1) return directions[0];

    int randIndex = getRandomValue(0, directions.size());
    return directions[randIndex];
}

Position RandMove::firstMoveProcess(Position& pos){
    currentDirection = getBestDirection(pos);
    Position resultPos = pos;
    moveTool.moveInDir(resultPos, currentDirection);
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


