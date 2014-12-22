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

    inline void setx(double x) {
        this->x = x;
    }

    inline double getx() const {
        return x;
    }

    inline void sety(double y) {
        this->y = y;
    }

    inline double gety() const {
        return y;
    }

    inline void setz(double z) {
        this->z = z;
    }

    inline double getz() const {
        return z;
    }

    inline void reset() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }

    inline void dump(const string &label = "") const {
        cout << label << x << " " << y << " " << z << endl;
    }
};

#endif	/* POINT_H */

