#include <stdlib.h>
#include "token.h"

char* token_class_strings[5] =
{
    "keyword",
    "identifier",
    "constant",
    "string literal",
    "punctuator",
    "eof"
};

token_list_t_node* make_token(char* l, token_class_t tc)
{
    token_t* token = malloc(sizeof(token_t));
    token->lexeme = l;
    token->t_class = tc;
    token_list_node_t* node = malloc(sizeof(token_list_node_t));
    node->token = token;
    node->next  = NULL;
    return node;
}

char* get_token_class_string(token_class_t tc)
{
    return token_class_strings[(int)tc];
}

void destroy_list(token_list_t** list)
{
    token_list_node_t* curr = (*list)->begin;
    token_list_node_t* next;
    while (curr != NULL)
    {
        next = curr->next;
        if (curr->token)
        {
            free(curr->token->lexeme);
            free(curr->token);
        }
        free(curr);
        curr = next;
    }
    *list = NULL;
}
