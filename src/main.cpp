#include <iostream>
#include <cstdlib>
#include <sysexits.h>
#include <string>

#include "include/Lox.hpp"

int main(int argc, char* argv[])
{
    if(argc > 2)
    {
        std::cout << "Usage: cpplox [script]\n";
        exit(EX_USAGE);
    } else if (argc == 2) {
        std::string path(argv[1]);
        runFile(path);
    } else {
        runPrompt();
    }
    return 0;
}