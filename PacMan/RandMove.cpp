#include "RandMove.h"

Position RandMove::getNextPosition(Position& current){   
    if (isInitialized) {
        //check direction
        //get next pint in this direction
        //check new position -if bad
            // get possible direction
            // if size ==1 -> okej
            // if size >1 - delete current dir, if 1 OK if more -> rand()
    }
    else {
        isInitialized = false;
        // get possible direction
        //check new position -if bad
            // get possible direction
            // if size ==1 -> okej
            // if size >1 - delete current dir, if 1 OK if more -> rand()
        // 
        //choose random direction but it must be good
    }
    return Position();
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
    
    directions.erase(std::remove(directions.begin(), directions.end(), currentDirection), 
                     directions.end());

    if (directions.size() == 1) return directions[0];

    int randIndex = getRandomValue(0, directions.size());
    return directions[randIndex];
}
