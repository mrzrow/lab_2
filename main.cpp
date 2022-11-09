#include <iostream>
#include <cstring>
#include "functions.h"

const char* flags[3] = {
    "--forward",
    "--reverse",
    "--file"
};

int main(int argc, char ** argv) {
    switch (argc) {
        case 1:
            std::cerr << "##### Nothing was read #####\n";
            usage();
            exit(1);
        case 2:
            if (!strcmp(argv[1], flags[0])) {
                read_from_cin();
                std::cout << "---Enter a mathematical expression in inormalized form---\n";
                forward();
            }
            else if (!strcmp(argv[1], flags[1])) {
                read_from_cin();
                std::cout << "---Enter mathematical expression in reverse polish notation form---\n";
                reverse();
            }
            else {
                std::cerr << "##### Worng flags #####\n";
                usage();
                exit(1);
            }
        case 4:
            if (!strcmp(argv[1], flags[2])) {
                char *filename = argv[2];
                if (read_from_file(filename)) {
                    std::cerr << "##### Provide file #####\n";
                    usage();
                    exit(1);
                }
                if (!strcmp(argv[3], flags[0])) {
                    std::cout << "---Enter a mathematical expression in inormalized form---\n";
                    forward();
                }
                else if (!strcmp(argv[3], flags[1])) {
                    std::cout << "---Enter mathematical expression in reverse polish notation form---\n";
                    reverse();
                }
            }
            else {
                std::cerr << "##### Worng flags #####\n";
                usage();
                exit(1);
            }
        default:
            std::cerr << "##### Worng flags or flags weren't entered #####\n";
            usage();
            exit(1);
    }

    exit(0);
}
