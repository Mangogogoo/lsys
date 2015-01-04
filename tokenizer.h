#ifndef TOKENIZER_H
#define	TOKENIZER_H

#include <string>
#include <vector>
#include <stdint.h>

using namespace std;

class tokenizer {
public:
    string get(string line, const char delimiter, uint32_t i);
};

string tokenizer::get(string line, const char delimiter, uint32_t i) {
    vector<string> tokens;
    string token;
    for (uint32_t j = 0; j < line.length(); ++j) {
        if (line[j] == delimiter) {
            if ((j > 0) && line[j - 1] != delimiter) {
                tokens.push_back(token);
                token = "";
            }
        } else
            token += line[j];
    }
    if (token != "") {
        cout << token << endl;
        tokens.push_back(token);
    }

    return i < tokens.size() ? tokens[i] : "";
}

#endif	/* TOKENIZER_H */

