#ifndef CONFIG_H
#define	CONFIG_H

#include <string>
#include <vector>
#include <map>
#include <cmath>
#include "utils.h"
#include "tokenizer.h"

using namespace std;

class config {
    map<string, string> properties;    
    
public:
    config(string path);
    string getValue(string key);    
};

config::config(string path) {
    vector<string> lines = loadTextFile(path);    
    tokenizer t;
    for (string line: lines) {
        string key = t.get(line, ' ', 1);
        string value = t.get(line, ' ', 3);
        properties.insert(pair<string, string>(key, value));
    }    
}

string config::getValue(string key) {
    return properties[key];
}

#endif	/* CONFIG_H */

