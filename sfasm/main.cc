#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <unordered_map>

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    printf("Please provide a file to assemble\n");
    return EXIT_FAILURE;
  }
  char* filename = argv[1];
  std::ifstream input(filename);
  if (!input.good())
  {
    printf("Can't open %s. No such file.\n", filename);
    return EXIT_FAILURE;
  }

  std::string line;
  int pass_indicator = 1;
  int location_counter = 0;
  while (getline(input, line))
  {
    printf("%s\n", line.c_str());
  }
  return EXIT_SUCCESS;
}
