#ifndef POINT_H
#define	POINT_H

#include <iostream>

class point {
    float x, y, z;
public:

    point() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }

    point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {
    }

    inline void setx(float x) {
        this->x = x;
    }

    inline float getx() const {
        return x;
    }

    inline void sety(float y) {
        this->y = y;
    }

    inline float gety() const {
        return y;
    }

    inline void setz(float z) {
        this->z = z;
    }

    inline float getz() const {
        return z;
    }
    inline void reset() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }
    inline void dump(const std::string &label = "") const {
        std::cout << label << x << " " << y << " " << z << endl;
    }
};

#endif	/* POINT_H */

