/* lexer.c
 *
 * Tediously hand-written lexer for exercise purposes
 * using a labeled state-machine approach inspired by
 * re2c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "../helpers.h"

token_list_node_t* scan(lex_context& ctx);

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
        if (next_node->token->t_class == TOKEN_END) break;
        pointer->next = next_node;
        pointer = next_node;
        (token_list->size)++;
    }

    return token_list;
}

token_list_node_t* scan(lex_context& ctx)
{
    const char* anchor = ctx.cursor++;
    char* cc;
    switch (cc = *ctx.cursor)
    {
        // EOF
        case 0x00: goto lexend;

        // non-linebreak whitespace
        case 0x08:
        case '\t':
        case '\v':
        case '\f':
        case ' ':

        // linebreak whitespace
        case '\n':
        case '\r':

        // punctuators

        // numeric characters

        // alphabetic characters
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':

        // keyword start characters
        case 'a':   goto lex01;
        case 'b':   goto lex02;
        case 'c':   goto lex03;
        case 'd':   goto lex04;
        case 'e':   goto lex05;
        case 'f':   goto lex06;
        case 'g':   goto lex07;
        case 'i':   goto lex08;
        case 'l':   goto lex09;
        case 'r':   goto lex10;
        case 's':   goto lex11;
        case 't':   goto lex12;
        case 'u':   goto lex13;
        case 'u':   goto lex14;
        case 'v':   goto lex15;
        case 'w':   goto lex16;
        case '_':   goto lex17;
        default:

lexend:   return make_token(anchor, TOKEN_END);
lexread: cc = *++ctx.cursor;
lexid:  switch(cc)
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '_':
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
            case 'G':
            case 'H':
            case 'I':
            case 'J':
            case 'K':
            case 'L':
            case 'M':
            case 'N':
            case 'O':
            case 'P':
            case 'Q':
            case 'R':
            case 'S':
            case 'T':
            case 'U':
            case 'V':
            case 'W':
            case 'X':
            case 'Y':
            case 'Z':
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z': goto lexread;
            default: 
lexidsink:      return make_token(, TOKEN_IDENTIFIER);
        }
lex01:  if ((cc = *++ctx.cursor) == 'u') goto lex18; else goto lexid;

    }
    return NULL;
}
