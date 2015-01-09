#ifndef LSYS_H_INCLUDED
#define LSYS_H_INCLUDED

#include <iostream>
#include <fstream>
#include <map>
#include <stdint.h>

#include "tokenizer.h"
#include "bounding_box.h"
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
    stack <double> angles;
    stack <point> positions;
    void iterate();
    void prepareSegment(double angle);
    bounding_box bb;
public:

    lsystem();
    void parse(string path);
    void addPair(char variable, string rule);
    void setStart(string start);
    void setIterationCount(uint32_t n);
    vector<point *> getVertices();
    bounding_box getBbox();
    void updateBbox(point c);
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

void lsystem::updateBbox(point p) {
    bb.update(p);
}

void lsystem::prepareSegment(double angle) {

    endPoint.setX((curPoint.getX()) + cos(angle));
    endPoint.setY((curPoint.getY()) + sin(angle));
    endPoint.setZ(curPoint.getZ());

    vertices.push_back(new point(curPoint));
    vertices.push_back(new point(endPoint));

    curPoint.setX(endPoint.getX());
    curPoint.setY(endPoint.getY());
    curPoint.setZ(endPoint.getZ());

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
                updateBbox(curPoint);
                break;
        }
    }
    return vertices;
}

bounding_box lsystem::getBbox() {


    return bb;
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
    tokenizer t;
    string line;
    vector<string> lines;   
    lines = loadTextFile(path);
    for (string line : lines) {
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
}

lsystem::~lsystem() {
    for (uint32_t i = 0; i < vertices.size(); ++i) {
        delete vertices[i];
    }
    vertices.clear();
}

#endif