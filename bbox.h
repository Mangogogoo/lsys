#ifndef BBOX_H
#define	BBOX_H

#include "point.h"

class bbox {
    point p0, p1; // p0 -> upper left, p1 - lower right
public:
    bbox();
    bbox(point p0, point p1);
    void setp0(point p0);
    void setp1(point p1);
    point getp0() const;
    point getp1() const;
    void dump();
};

bbox::bbox() {
}

bbox::bbox(point p0, point p1) {
    this->p0 = p0;
    this->p1 = p1;
}

void bbox::setp0(point p0) {
    this->p0 = p0;
}

void bbox::setp1(point p1) {
    this->p1 = p1;
}

point bbox::getp0() const {
    return p0;
}

point bbox::getp1() const {
    return p1;
}

void bbox::dump() {
    cout << p0.getx() << " " << p0.gety() << " " << p1.getx() << " " << p1.gety() << endl;
}



#endif	/* BBOX_H */

