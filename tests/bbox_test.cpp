#include <cassert>
#include "../bbox.h"

using namespace std;

int main(int argc, char** argv) {
    bbox bb;
    
    point upperLeft(-1, 1, 0);
    point lowerRight(1, -1, 0);
    bb.setLowerRight(lowerRight);
    bb.setUpperLeft(upperLeft);
    
    assert(bb.getCenterX() == 0);
    assert(bb.getCenterY() == 0);
    assert(bb.getHeight() == 2);
    assert(bb.getWidth() == 2);
    
    return 0;
}

