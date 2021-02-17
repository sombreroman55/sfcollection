#ifndef TOKEN_H
#define TOKEN_H

typedef enum
{
  TOKEN_KEYWORD,
  TOKEN_IDENTIFIER,
  TOKEN_CONSTANT,
  TOKEN_STRING_LITERAL,
  TOKEN_PUNCTUATOR,
  TOKEN_END             // special EOF token
} token_class_t;

typedef struct
{
  token_class_t t_class;
  char* lexeme;
} token_t;

typedef struct token_list_node_t
{
  token_t* token;
  struct token_list_node_t* next;
} token_list_node_t;

typedef struct
{
  int size;
  token_list_node_t* begin;
} token_list_t;

char* get_token_class_string(token_class_t tc);
token_list_node_t* make_token(char* l, token_class_t tc);
void destroy_list(token_list_t** list);

#endif /* TOKEN_H */
