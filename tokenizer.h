#ifndef EXTRACTOR_H
#define	EXTRACTOR_H

#include <string>
#include <vector>

using namespace std;

class tokenizer {
public:
    static string get(string line, char delimiter, uint32_t i);
};

string tokenizer::get(string line, char delimiter, uint32_t i) {
    vector<string> tokens;
    size_t startPoint = 0, endPoint;
    while ((endPoint = line.find(delimiter, startPoint)) != string::npos) {
        if (endPoint != startPoint) tokens.push_back(line.substr(startPoint, endPoint - startPoint));
        if (endPoint + 1 < line.length()) startPoint = endPoint + 1; else break;
    } 
    if (endPoint != line.length()) tokens.push_back(line.substr(startPoint, string::npos));  
    if (tokens.size() > i) return tokens[i];
    else return "";
}

#endif	/* EXTRACTOR_H */

