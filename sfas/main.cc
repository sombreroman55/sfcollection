/* main.cc
 *
 * Main program
 *
 */

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>

#include "sfas.hh"
using namespace sfas;

int main(int argc, char** argv)
{
    printf("sfas - SNES/Super Famicom assembler\n");
    if (argc < 2)
    {
        printf("Please provide a file to assemble\n");
        return EXIT_FAILURE;
    }

    // TODO: command-line flags

    auto assembler = std::make_unique<SFAS>();
    for (int i = 1; i < argc; i++)
    {
        char* filename = argv[i];
        std::ifstream input(filename);
        if (!input.good())
        {
            printf("Can't open %s. No such file.\n", filename);
            continue;
        }
        std::stringstream src_buffer;
        src_buffer << input.rdbuf();
        assembler->assemble(src_buffer.str());
    }
    return EXIT_SUCCESS;
}
