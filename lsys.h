#ifndef LSYS_H_INCLUDED
#define LSYS_H_INCLUDED

#include <iostream>
#include <fstream>
#include <map>
#include <stdint.h>

#include "tokenizer.h"
#include "point.h"
#include "utils.h"

using namespace std;

class lsystem {
    map<char, string> rewritingPairs; // variable, rule pair
    string start, chain;    
    uint32_t iterationsCount;
    double angle, gangle;
    float extractAngle(string line);
    vector<point *> vertices;
    point startPoint, endPoint, curPoint;
    gstack <double> angles;
    gstack <point> positions;
    void iterate();
    void prepareSegment(double angle);

public:

    lsystem();
    void parse(string path);
    void addPair(char variable, string rule);
    void setStart(string start);
    void setIterationCount(uint32_t n);
    vector<point *> getVertices();
    void setAngle(double angle);
    double getAngle() const;
    string getChain();
    void show();
    void reset();
    ~lsystem();
};

lsystem::lsystem() {
    gangle = 0.0;
}

void lsystem::addPair(char variable, string rule) {
    rewritingPairs.insert(pair<char, string>(variable, rule));
}

void lsystem::setStart(string start) {
    this->start = start;
    chain = start;
}

void lsystem::setIterationCount(uint32_t n) {
    this->iterationsCount = n;
}

void lsystem::iterate() {
    string temp;
    for (uint32_t k = 0; k < iterationsCount; ++k) {
        temp = "";
        for (uint32_t i = 0; i < chain.length(); ++i) {
            if (rewritingPairs[chain[i]] != "") temp += rewritingPairs[chain[i]];
            else temp += chain[i];
        }
        chain = temp;
    }
}

void lsystem::prepareSegment(double angle) {

    /* TODO: remove scaling */
    endPoint.setx((curPoint.getx()) + 2.0 * cos(angle));
    endPoint.sety((curPoint.gety()) + 2.0 * sin(angle));
    endPoint.setz(curPoint.getz());

    vertices.push_back(new point(curPoint));
    vertices.push_back(new point(endPoint));

    curPoint.setx(endPoint.getx());
    curPoint.sety(endPoint.gety());
    curPoint.setz(endPoint.getz());

}

vector<point *> lsystem::getVertices() {

    this->iterate();

    string chain = this->getChain();

    for (uint32_t i = 0; i < chain.length(); ++i) {
        switch (chain[i]) {
            case '+':
                gangle += deg2rad(getAngle());
                break;
            case '-':
                gangle -= deg2rad(getAngle());
                break;
            case '[':
                positions.push(curPoint);
                angles.push(gangle);
                break;
            case ']':
                curPoint = positions.pop();
                gangle = angles.pop();
                break;
            default:
                prepareSegment(gangle);
                break;
        }
    }
    return vertices;
}

string lsystem::getChain() {
    return chain;
}

// degrees

void lsystem::setAngle(double angle) {
    this->angle = angle;
}

double lsystem::getAngle() const {
    return angle;
}

void lsystem::show() {
    cout << chain << endl;
}

void lsystem::reset() {
    start = "";
    chain = "";
}

void lsystem::parse(string path) {
    this->reset();
    ifstream f;
    string line;
    f.open(path.c_str());
    tokenizer t;
    while (!f.eof()) {
        getline(f, line);
        switch (line [0]) {
            case 'A': this->setAngle(atof(t.get(line, ' ', 1).c_str()));
                break;
                break;
            case 'P': this->addPair(t.get(line, ' ', 1)[0], t.get(line, ' ', 2));
                break;
                break;
            case 'S': this->setStart(t.get(line, ' ', 1));
                break;
                break;
            case 'I': this->setIterationCount(atoi(t.get(line, ' ', 1).c_str()));
                break;
                break;
            default:
                ; // TODO: log unknown command
        }
    }

    f.close();
}

lsystem::~lsystem() {
    for (uint32_t i = 0; i < vertices.size(); ++i) {
        delete vertices[i];
    }
    vertices.clear();
}

#endif