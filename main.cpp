#include <iostream>
#include <cstring>
#include "functions.h"

const char* flags[4] = {
    "--forward",
    "--reverse",
    "--file",
    "--help"
};

int main(int argc, char ** argv) {
    switch (argc) {
        case 1:
            std::cerr << "##### Flags weren't read #####\n";
            usage();
            exit(1);
        case 2:
            if (!strcmp(argv[1], flags[3])) {
                usage();
                exit(0);
            }
            if (!strcmp(argv[1], flags[0])) {
                std::cout << "Enter a mathematical expression in inormalized form:\n>> ";
                read_from_cin();
                forward();
            }
            else if (!strcmp(argv[1], flags[1])) {
                std::cout << "Enter a mathematical expression in reverse polish notation form:\n>> ";
                read_from_cin();
                reverse();
            }
            else {
                std::cerr << "##### Worng flags #####\n";
                usage();
                exit(1);
            }
            break;
        case 4:
            if (!strcmp(argv[1], flags[2])) {
                char *filename = argv[2];
                if (read_from_file(filename)) {
                    std::cerr << "##### Provide file #####\n";
                    usage();
                    exit(1);
                }
                if (!strcmp(argv[3], flags[0])) {
                    std::cout << "A mathematical expression in inormalized form\n";
                    forward();
                }
                else if (!strcmp(argv[3], flags[1])) {
                    std::cout << "A mathematical expression in reverse polish notation form\n";
                    reverse();
                }
            }
            else {
                std::cerr << "##### Worng flags #####\n";
                usage();
                exit(1);
            }
            break;
        default:
            std::cerr << "##### Worng flags #####\n";
            usage();
            exit(1);
    }

    exit(0);
}
