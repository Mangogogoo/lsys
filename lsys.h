#ifndef LSYS_H_INCLUDED
#define LSYS_H_INCLUDED

#include <iostream>
#include <map>
#include <stdint.h>

class glsystem {
    std::map<char, std::string> rewritingPairs; // variable, rule pair
    std::string start;
    std::string chain;
public:
    
    glsystem();
    void addPair(char variable, std::string rule);
    void setStart(std::string start);
    void iterate(uint32_t n);
    std::string getChain();
    void show();
    void reset();
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
std::string glsystem::getChain() {
    return chain;
}
void glsystem::show() {
    std::cout << chain << std::endl;
}
void glsystem::reset() {
    start = "";
    chain = "";
}
glsystem::~glsystem() {

}


#endif // LSYS_H_INCLUDED
