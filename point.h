#ifndef POINT_H
#define	POINT_H

#include <iostream>

using namespace std;

class point {
    double x, y, z;
public:

    point() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }

    point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {
    }

    void setX(double x) {
        this->x = x;
    }

    double getX() const {
        return x;
    }

    void setY(double y) {
        this->y = y;
    }

    double getY() const {
        return y;
    }

    void setZ(double z) {
        this->z = z;
    }

    double getZ() const {
        return z;
    }

    void reset() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }

    void dump(const string &label = "") const {
        cout << label << x << " " << y << " " << z << endl;
    }
};

#endif	/* POINT_H */

