#ifndef UTILS_H
#define	UTILS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

double deg2rad(double a) {
    return a * M_PI / 180.0;
}

vector<string> loadTextFile(string path) {
    vector<string> lines;
    ifstream f;
    string line;
    f.open(path.c_str());
    if (!f.fail()) {
        while (!f.eof()) {
            getline(f, line);
            lines.push_back(line);
        }
    }
    f.close();
    return lines;
}


#endif	/* UTILS_H */

