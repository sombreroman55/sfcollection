#include <iostream>
#include <fstream>
#include <string>

#include "frontend/lexer.hh"
using namespace SFCC::Frontend;
using namespace SFCC::DataStructures;

// TODO: Add command-line argument parsing here

int main (int argc, char** argv)
{
    std::cout << "SFCC Super Famicom C compiler" << std::endl;

    for (int i = 1; i < argc; i++)
    {
        std::string file(argv[i]);
        std::cout << "\t" << file << std::endl;
        std::ifstream filestream;
        filestream.open(file, std::ios::in);
        filestream.close();
    }

    return 0;
}
