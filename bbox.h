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
    if (p.getX() > lowerRight.getX()) lowerRight.setX(p.getX());
    if (p.getX() < upperLeft.getX()) upperLeft.setX(p.getX());

    if (p.getY() < lowerRight.getY()) lowerRight.setY(p.getY());
    if (p.getY() > upperLeft.getY()) upperLeft.setY(p.getY());

}

void bbox::dump() {
    cout << upperLeft.getX() << " " << upperLeft.getY() << " " << lowerRight.getX() << " " << lowerRight.getY() << endl;
    cout << this->getWidth() << " " << this->getHeight() << endl;
}

double bbox::getHeight() const {
    return upperLeft.getY() - lowerRight.getY();
}

double bbox::getWidth() const {
    return lowerRight.getX() - upperLeft.getX();
}

double bbox::getCenterX() const {
    return (upperLeft.getX() + lowerRight.getX()) / 2.0;
}

double bbox::getCenterY() const {
    return (upperLeft.getY() + lowerRight.getY()) / 2.0;
}

#endif	/* BBOX_H */

