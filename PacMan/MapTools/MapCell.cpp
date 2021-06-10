#include "MapCell.h"

bool MapCell::getPoint(){
    if (point) {
        point = false;
    }
    return point;
}

bool MapCell::isObstacle()
{
    if (category == Category::OBSTACLE) return true;
    return false;
}
