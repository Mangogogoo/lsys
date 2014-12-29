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
    double getWidth() const;
    double getHeight() const;
    double getCenterX() const;
    double getCenterY() const;
    void update(point p);
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

void bbox::update(point p) {
    if (p.getx() > lowerRight.getx()) lowerRight.setx(p.getx());
    if (p.getx() < upperLeft.getx()) upperLeft.setx(p.getx());

    if (p.gety() < lowerRight.gety()) lowerRight.sety(p.gety());
    if (p.gety() > upperLeft.gety()) upperLeft.sety(p.gety());

}

void bbox::dump() {
    cout << upperLeft.getx() << " " << upperLeft.gety() << " " << lowerRight.getx() << " " << lowerRight.gety() << endl;
    cout << this->getWidth() << " " << this->getHeight() << endl;
}

double bbox::getHeight() const {
    return upperLeft.gety() - lowerRight.gety();
}

double bbox::getWidth() const {
    return lowerRight.getx() - upperLeft.getx();
}

double bbox::getCenterX() const {
    return (upperLeft.getx() + lowerRight.getx()) / 2.0;
}

double bbox::getCenterY() const {
    return (upperLeft.gety() + lowerRight.gety()) / 2.0;
}

#endif	/* BBOX_H */

