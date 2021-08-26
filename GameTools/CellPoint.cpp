#include "CellPoint.h"


int CellPoint::getPoints()const {
    return static_cast<int>(point);
}

int CellPoint::takePoints(){
    int res = getPoints();
    point = PointCat::ZER0;
    return res;
}

PointCat CellPoint::getPointClass() const{
    return point;
}
