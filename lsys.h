#ifndef LSYS_H_INCLUDED
#define LSYS_H_INCLUDED

#include <iostream>
#include <map>
#include <stdint.h>

class glsystem {
    std::map<char, std::string> rewritingPairs; // variable, rule pair
    std::string start;
public:
    std::string chain;
    glsystem();
    void addPair(char variable, std::string rule);
    void setStart(std::string start);
    void iterate(uint32_t n);
    void show();
    ~glsystem();
};

glsystem::glsystem() {

}

void glsystem::addPair(char variable, std::string rule) {
    rewritingPairs.insert(pair<char, std::string>(variable, rule));
}

void glsystem::setStart(string start) {
    this->start = start;
    chain = start;
}

void glsystem::iterate(uint32_t n) {
    std::string temp;
    for (uint32_t k = 0; k < n; ++k) {
        temp = "";
        for (uint32_t i = 0; i < chain.length(); ++i) {
            if (rewritingPairs[chain[i]] != "") temp += rewritingPairs[chain[i]];
            else temp += chain[i];
        }
        chain = temp;
    }
}

void glsystem::show() {
    std::cout << chain << std::endl;
}

glsystem::~glsystem() {

}


#endif // LSYS_H_INCLUDED
