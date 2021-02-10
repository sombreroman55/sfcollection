#include <stdio.h>
#include "helpers.h"

void print_usage()
{
    printf("Usage:\n");
    printf("    TODO: fill me in!\n");
}

void print_file_not_found(char* filename)
{
    printf("Compilation failed!\n");
    printf("No such file %s!\n", filename);
}

void print_token_info(token_t token)
{
    printf("<\"%s\", \"%s\">\n", token.lexeme, get_token_class_string(token.t_class));
}
