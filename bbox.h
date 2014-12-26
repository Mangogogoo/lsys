#ifndef BBOX_H
#define	BBOX_H

#include "point.h"

class bbox {
    point upperLeft, lowerRight; 
public:
    bbox();
    bbox(point upperLeft, point lowerRight);
    void setUpperLeft(point upperLeft);
    void setLowerRight(point lowerRight);
    point getUpperLeft() const;
    point getLowerRight() const;
    void dump();
};

bbox::bbox() {
}

bbox::bbox(point upperLeft, point lowerRight) {
    this->upperLeft = upperLeft;
    this->lowerRight = lowerRight;
}

void bbox::setUpperLeft(point upperLeft) {
    this->upperLeft = upperLeft;
}

void bbox::setLowerRight(point lowerRight) {
    this->lowerRight = lowerRight;
}

point bbox::getUpperLeft() const {
    return upperLeft;
}

point bbox::getLowerRight() const {
    return lowerRight;
}

void bbox::dump() {
    cout << upperLeft.getx() << " " << upperLeft.gety() << " " << lowerRight.getx() << " " << lowerRight.gety() << endl;
}



#endif	/* BBOX_H */

