#ifndef LSYS_H_INCLUDED
#define LSYS_H_INCLUDED

#include <iostream>
#include <vector>
#include <stdint.h>

using namespace std;

class glsystem {
    vector<char> vecVariables;
    vector<string> vecRules;
    vector<char> vecConstants;
    string start;

public:
    string chain;
    glsystem();
    void addVariable(char v);
    void addRule(string r);
    void setStart(string s);
    void iterate(uint32_t n);
    void show();
    ~glsystem();
};

glsystem::glsystem() {

}

void glsystem::addVariable(char v) {
    vecVariables.push_back(v);
}

void glsystem::addRule(string r) {
    vecRules.push_back(r);
}

void glsystem::setStart(string s) {
    start = s;
    chain = start;
}

void glsystem::iterate(uint32_t n) {
    string temp;
    bool hit = false;
    for (uint32_t k = 0; k < n; ++k) {
        temp = "";
        for (uint32_t i = 0; i < chain.length(); ++i) {
            hit = false;
            for (uint32_t j = 0; j < vecVariables.size(); ++j) {
                if (chain[i] == vecVariables[j]) {
                    temp += vecRules[j];
                    hit = true;
                }
            }
            if (!hit) {
                temp += chain[i];
            }
        }
        chain = temp;
    }
}

void glsystem::show() {
    cout << chain << endl;
}

glsystem::~glsystem() {

}


#endif // LSYS_H_INCLUDED
