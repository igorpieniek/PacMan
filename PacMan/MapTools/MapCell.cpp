#include "MapCell.h"


bool MapCell::isObstacle()
{
    if (category == Category::OBSTACLE) return true;
    return false;
}
