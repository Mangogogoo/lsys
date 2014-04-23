#ifndef LSYS_H_INCLUDED
#define LSYS_H_INCLUDED

#include <iostream>
#include <vector>

// api dependency: none
// platform depenedency: none
// last modification date: 06.03.2009
// start date: 06.03.2009
// description: generic l-system engine
// todo:
// changes:


using namespace std;

class glsystem
{
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
    void iterate(int n);
    void show();
    ~glsystem();
};


glsystem::glsystem()
{

}

void glsystem::addVariable(char v)
{
    vecVariables.push_back(v);
}

void glsystem::addRule(string r)
{
    vecRules.push_back(r);
}


void glsystem::setStart(string s)
{
    start = s;
    chain = start;
}


void glsystem::iterate(int n)
{
    string temp;
    bool hit = false;
    for (int k = 0; k < n; ++k)
    {
        temp = "";
        for (int i = 0; i < chain.length(); ++i)
        {
            hit = false;
            for (int j = 0; j < vecVariables.size(); ++j)
            {
                if (chain[i] == vecVariables[j])
                {
                    temp += vecRules[j];
                    hit = true;
                }
            }
            if (!hit)
            {
                temp += chain[i];
            }
        }
        chain = temp;
    }
}

void glsystem::show()
{
    cout << chain << endl;
}

glsystem::~glsystem()
{

}


#endif // LSYS_H_INCLUDED
