/*
 *
 *
 *
 *
 */

#include <string>
#include "token.hh"

namespace sfas
{
  Token::Token()
  {
    type_ = TokenType::TT_NONE;
  }

  Token::Token(TokenType type, std::string lexeme) :
    type_(type), lexeme_(lexeme) {}

  Token::~Token() = default;

  std::string Token::get_lexeme(void)
  {
    return lexeme_;
  }

  std::string Token::to_string(void)
  {
    std::string l = get_lexeme();
    if (l == "\n")
    {
      l = "\\n";
    }
    else if (l == "\0")
    {
      l = "EOF";
    }
    return "<" + tokenTypeStrs[(int)type_] + ", \"" + l + "\">";
  }
}
