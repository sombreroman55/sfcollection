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
// #include "sfas.hh"
// #include "lexer.hh"
// #include "token.hh"
// using namespace sfas;

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

  // auto assembler = std::make_unique<SFAS>();
  for (int i = 1; i < argc; i++)
  {
    std::string filename(argv[i]);
    std::ifstream input(filename);
    if (!input.good())
    {
      printf("Can't open %s. No such file.\n", filename.c_str());
      continue;
    }
    else
    {
      printf("Opened %s!\n", filename.c_str());
    }
    // std::stringstream src_buffer;
    // src_buffer << input.rdbuf();
    // assembler->assemble(src_buffer.str());
    // std::cout << src_buffer.str() << std::endl;
    // auto lexer = std::make_unique<Lexer>();
    // auto tokens = lexer->tokenize_line(src_buffer.str(), 1);
    // for (auto token : tokens) std::cout << token.get_lexeme() << std::endl;
  }
  return EXIT_SUCCESS;
}
