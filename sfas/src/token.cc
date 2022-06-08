/*
 *
 *
 *
 *
 */

#include <string>
#include "location.hh"
#include "token.hh"

namespace sfas
{
    Token::Token(TokenType type, std::string lexeme, Location loc) :
        type_(type), lexeme_(lexeme), location_(loc) {}

    Token::~Token() = default;

    std::string Token::get_lexeme(void)
    {
        return lexeme_;
    }
}
