#ifndef LSYS_H_INCLUDED
#define LSYS_H_INCLUDED

#include <iostream>
#include <fstream>
#include <map>
#include <stdint.h>

#include "tokenizer.h"

using namespace std;

class lsystem {
    map<char, string> rewritingPairs; // variable, rule pair
    string start, chain;
    float angle;
    uint32_t iterationsCount;
    float extractAngle(string line);
public:

    lsystem();
    void parse(string path);
    void addPair(char variable, string rule);
    void setStart(string start);
    void setIterationCount(uint32_t n);
    void iterate();
    void setAngle(float angle);
    float getAngle() const;
    string getChain();
    void show();
    void reset();
    ~lsystem();
};

lsystem::lsystem() {

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

string lsystem::getChain() {
    return chain;
}

// degrees

void lsystem::setAngle(float angle) {
    this->angle = angle;
}

float lsystem::getAngle() const {
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


}

#endif