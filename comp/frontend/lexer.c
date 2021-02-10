#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "../helpers.h"

int is_allowed_char (char c)
{
    return (isalpha(c) || c == '_');
}

int is_keyword(char* word)
{
    return ((!strcmp(word, "auto"      )) ||
            (!strcmp(word, "break"     )) ||
            (!strcmp(word, "case"      )) ||
            (!strcmp(word, "char"      )) ||
            (!strcmp(word, "const"     )) ||
            (!strcmp(word, "continue"  )) ||
            (!strcmp(word, "default"   )) ||
            (!strcmp(word, "do"        )) ||
            (!strcmp(word, "double"    )) ||
            (!strcmp(word, "else"      )) ||
            (!strcmp(word, "enum"      )) ||
            (!strcmp(word, "extern"    )) ||
            (!strcmp(word, "float"     )) ||
            (!strcmp(word, "for"       )) ||
            (!strcmp(word, "goto"      )) ||
            (!strcmp(word, "if"        )) ||
            (!strcmp(word, "inline"    )) ||
            (!strcmp(word, "int"       )) ||
            (!strcmp(word, "long"      )) ||
            (!strcmp(word, "register"  )) ||
            (!strcmp(word, "restrict"  )) ||
            (!strcmp(word, "return"    )) ||
            (!strcmp(word, "short"     )) ||
            (!strcmp(word, "signed"    )) ||
            (!strcmp(word, "sizeof"    )) ||
            (!strcmp(word, "static"    )) ||
            (!strcmp(word, "struct"    )) ||
            (!strcmp(word, "switch"    )) ||
            (!strcmp(word, "typedef"   )) ||
            (!strcmp(word, "union"     )) ||
            (!strcmp(word, "unsigned"  )) ||
            (!strcmp(word, "void"      )) ||
            (!strcmp(word, "volatile"  )) ||
            (!strcmp(word, "while"     )) ||
            (!strcmp(word, "_Bool"     )) ||
            (!strcmp(word, "_Complex"  )) ||
            (!strcmp(word, "_Imaginary")));
}

token_list_node_t* scan(FILE* fp)
{
    token_list_node_t* node = malloc(sizeof(token_list_node_t));
    node->token = NULL;
    node->next  = NULL;

    char c;

    while ((c = fgetc(fp)) && c != EOF)
    {
        if (is_allowed_char(c))
        {
            int size = 0;
            char* buffer = malloc(size * sizeof(char));
            do
            {
                size++;
                buffer = realloc(buffer, size * sizeof(char));
                buffer[size-1] = c;
                c = fgetc(fp);
            } while (c != EOF && is_allowed_char(c));

            size++;
            buffer = realloc(buffer, size * sizeof(char));
            buffer[size-1] = '\0';

            if (is_keyword(buffer))
            {
                token_t* token = malloc(sizeof(token_t));
                token->lexeme = buffer;
                token->t_class = KEYWORD;
                node->token = token;
                return node;
            }
            else
            {
                free(buffer);
            }
        }
    }

    return NULL;
}

token_list_t* lex(char* filename)
{
    token_list_t*      token_list = malloc(sizeof(token_list_t));
    token_list_node_t* begin_node = malloc(sizeof(token_list_node_t));

    begin_node->token = NULL;

    token_list->size = 0;
    token_list->begin = begin_node;

    token_list_node_t* pointer = begin_node;

    FILE* fp = fopen(filename, "r");

    while (1)
    {
        token_list_node_t* next_node = scan(fp);
        if (!next_node) break;
        pointer->next = next_node;
        pointer = next_node;
        (token_list->size)++;
    }

    return token_list;
}
