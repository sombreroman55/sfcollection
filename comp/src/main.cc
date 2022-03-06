#include <iostream>
#include <fstream>
#include <string>

#include "frontend/lexer.hh"
using namespace SFCC::Frontend;
using namespace SFCC::DataStructures;

int main (int argc, char** argv)
{
    std::cout << "SFCC Super Famicom C compiler" << std::endl;

    // Open files
    std::ifstream* source_files;
    source_files = new std::ifstream[argc];
    for (int i = 1; i < argc; i++)
    {
        std::string file(argv[i]);
        std::cout << "\t" << file << std::endl;
        source_files[i].open(file, std::ios::in);
    }

    for (int i = 1; i < argc; i++)
    {
        source_files[i].close();
    }

    delete[] source_files;

    return 0;
}
