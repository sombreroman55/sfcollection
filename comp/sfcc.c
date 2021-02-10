#include <stdio.h>
#include <stdlib.h>
#include "frontend/lexer.h"
#include "ds/token.h"
#include "helpers.h"

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        print_usage();
        exit(EXIT_FAILURE);
    }

    
    // Verify existence of each file passed in
    int argi;
    FILE* file;
    for (argi = 1; argi < argc; argi++)
    {
        if ((file = fopen(argv[argi],"r")) != NULL)
        {
            // File exists, close to avoid memory leak
            fclose(file);
        }
        else
        {
            print_file_not_found(argv[argi]);
            exit(EXIT_FAILURE);
        }
    }

    // Run frontend
    for (argi = 1; argi < argc; argi++)
    {
        // Run lexer on each file
        token_list_t* tokens = lex(argv[argi]);
        printf("List size: %d\n", tokens->size);

        token_list_node_t* curr = tokens->begin;
        int i;
        for (i = 0; i < tokens->size; i++)
        {
            curr = curr->next;
            print_token_info(*(curr->token));
        }
        destroy_list(&tokens);
        free(tokens);

        // Run parser on each file
        // Run semantic analysis on each file
    }

    // Optimize
    // Run backend

    exit(EXIT_SUCCESS);
}
