#include <iostream>
#include <cstring>
#include "functions.h"

int main(int argc, char ** argv) {
    if (argc == 1) {
        std::cerr << "Nothing was read\n";
        return 1;
    }

    if (argc == 2) {
        std::cout << "Enter a mathematical expression:\n";
        read_from_cin();
        if (strcmp(argv[1], "--forward") == 0)
            forward();
        else if (strcmp(argv[1], "--reverse") == 0)
            reverse();
    }
    else if (argc == 4 && strcmp(argv[1], "--file") == 0) {
        std::cout << "Enter a mathematical expression:\n";
        char *file_name = argv[2];
        std::cout << file_name;
        read_from_file(file_name);
        if (strcmp(argv[3], "--forward") == 0)
            forward();
        else if (strcmp(argv[3], "--reverse") == 0)
            reverse(); 
    }
    else { 
        std::cerr << "Worng flags\n";
        return 1;
    }

    return 0;
}
