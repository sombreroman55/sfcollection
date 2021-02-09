#include "token.h"

char* token_class_strings[5] =
{
    "keyword",
    "identifier",
    "constant",
    "string literal",
    "punctuator"
};

char* get_token_class_string(token_class_t tc)
{
    return token_class_strings[(int)tc];
}
