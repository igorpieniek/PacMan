#include "MapCell.h"


bool MapCell::isObstacle() const
{
    if (category == Category::OBSTACLE) return true;
    return false;
}
