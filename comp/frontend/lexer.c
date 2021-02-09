#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

token_list_t* lex(char* filename)
{
    token_list_t*      token_list = malloc(sizeof(token_list_t));
    token_list_node_t* begin_node = malloc(sizeof(token_list_node_t));
    token_list->size = 0;
    token_list->begin = begin_node;

    token_t* token = malloc(sizeof (token_t));
    token->source_element = "meme";
    token->t_class = KEYWORD;

    begin_node->token = token;
    begin_node->next = NULL;
    (token_list->size)++;
    return token_list;
}
