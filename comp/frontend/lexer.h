#ifndef LEXER_H
#define LEXER_H

#include "../ds/token.h"

token_list_t* lex(char* filename);

typedef struct
{
  char* input_stream;
  char* cursor;
} lex_context;

#endif /* LEXER_H */
