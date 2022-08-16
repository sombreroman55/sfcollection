/* main.cc
 *
 * Main program
 *
 */

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#include "config.hh"
#include "sfas.hh"
using namespace sfas;

int main(int argc, char** argv)
{
  printf("sfas - SNES/Super Famicom assembler\n");
  printf("VERSION %d.%d.%d\n\n", sfas_VERSION_MAJOR, sfas_VERSION_MINOR, sfas_VERSION_PATCH);
  if (argc < 2)
  {
    printf("Please provide a file to assemble\n");
    return EXIT_FAILURE;
  }

  // TODO: command-line flags

  for (int i = 1; i < argc; i++)
  {
    std::string filename(argv[i]);
    std::ifstream input(filename);
    if (!input.good())
    {
      printf("Can't open %s. No such file.\n", filename.c_str());
      continue;
    }
    std::stringstream src_stream;
    src_stream << input.rdbuf();
    std::string src_buffer = src_stream.str();
    if (src_buffer.back() != '\n') src_buffer.push_back('\n');
    SFAS assembler(filename, src_buffer);
    assembler.assemble();
  }
  return EXIT_SUCCESS;
}
