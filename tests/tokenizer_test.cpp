#include <iostream>
#include <cassert>

#include "../tokenizer.h"


int main(int argc, char *argv[]) {
    tokenizer t;
    assert(t.get("quick fox jumps over the lazy dog", ' ', 1) != "quick");
    assert(t.get("quick fox jumps over the lazy dog", ' ', 1) != "dog");
    
    return 0;
}
