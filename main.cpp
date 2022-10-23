#include <iostream>
#include <string.h>
#include "functions.h"

int main(int argc, char ** argv) {
    if (argc == 1) {
        std::cerr << "Nothing was read\n";
        return 1;
    }

    for (std::size_t i = 1; i <= argc; ++i) {
        if (strcmp(argv[i], "--forward") == 0)
            forward();
        if (strcmp(argv[i], "--reverse") == 0)
            reverse();
    }
    return 0;
}
