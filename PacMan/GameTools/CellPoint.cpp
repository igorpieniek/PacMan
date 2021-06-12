#include "CellPoint.h"

int CellPoint::getPoints(){
    int res = static_cast<int>(point);
    point = PointCat::ZER0;
    return res;
}
