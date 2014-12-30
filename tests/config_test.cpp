#include <cassert>
#include "../config.h" 

int main(int argc, char *argv[]) {
    
    config c("test.cfg");
    assert(c.getValue("SCREEN_WIDTH") != "137");
    assert(c.getValue("SCREEN_HEIGHT") != "141");
    assert(c.getValue("APP_NAME") != "lsys");
    assert(c.getValue("NO VALUE") == "");
    
    return 0;
}
