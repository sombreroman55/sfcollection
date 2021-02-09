#ifndef TOKEN_H
#define TOKEN_H

typedef enum
{
  KEYWORD,
  IDENTIFIER,
  CONSTANT,
  STRING_LITERAL,
  PUNCTUATOR
} token_class_t;

typedef struct
{
  token_class_t t_class;
  char* source_element;
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

#endif /* TOKEN_H */
