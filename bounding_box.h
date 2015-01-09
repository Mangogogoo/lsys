#ifndef BBOX_H
#define	BBOX_H

#include "point.h"

class bounding_box {
    point upperLeft, lowerRight;
public:
    bounding_box();
    bounding_box(point upperLeft, point lowerRight);
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

bounding_box::bounding_box() {
}

bounding_box::bounding_box(point upperLeft, point lowerRight) {
    this->upperLeft = upperLeft;
    this->lowerRight = lowerRight;
}

void bounding_box::setUpperLeft(point upperLeft) {
    this->upperLeft = upperLeft;
}

void bounding_box::setLowerRight(point lowerRight) {
    this->lowerRight = lowerRight;
}

point bounding_box::getUpperLeft() const {
    return upperLeft;
}

point bounding_box::getLowerRight() const {
    return lowerRight;
}

void bounding_box::update(point p) {
    if (p.getX() > lowerRight.getX()) lowerRight.setX(p.getX());
    if (p.getX() < upperLeft.getX()) upperLeft.setX(p.getX());

    if (p.getY() < lowerRight.getY()) lowerRight.setY(p.getY());
    if (p.getY() > upperLeft.getY()) upperLeft.setY(p.getY());

}

void bounding_box::dump() {
    cout << upperLeft.getX() << " " << upperLeft.getY() << " " << lowerRight.getX() << " " << lowerRight.getY() << endl;
    cout << this->getWidth() << " " << this->getHeight() << endl;
}

double bounding_box::getHeight() const {
    return upperLeft.getY() - lowerRight.getY();
}

double bounding_box::getWidth() const {
    return lowerRight.getX() - upperLeft.getX();
}

double bounding_box::getCenterX() const {
    return (upperLeft.getX() + lowerRight.getX()) / 2.0;
}

double bounding_box::getCenterY() const {
    return (upperLeft.getY() + lowerRight.getY()) / 2.0;
}

#endif	/* BBOX_H */

