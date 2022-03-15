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
        std::string filename = argv[i];
        std::ifstream f(filename);
        std::string buffer(std::istreambuf_iterator<char>(f), {});
        std::cout << buffer << std::endl;
        Lexer lexer(filename, buffer);
        std::vector<Token> tokens = lexer.lex();

        for (int i = 0; i < tokens.size(); i++)
        {
            std::cout << tokens[i].to_string() << std::endl;
        }
    }

    return 0;
}
