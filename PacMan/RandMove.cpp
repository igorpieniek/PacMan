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

    return Position();
}

Direction RandMove::getBestDirection(Position& center){

    return Direction();
}
