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
    type_ = TokenType::NONE;
  }

  Token::Token(TokenType type, std::string lexeme) :
    type_(type), lexeme_(lexeme) {}

  Token::Token(TokenType type, std::string lexeme, uint16_t value) :
    type_(type), lexeme_(lexeme), value_(value) {}

  Token::~Token() = default;

  std::string Token::get_lexeme(void)
  {
    return lexeme_;
  }

  std::string Token::to_string(void)
  {
    std::string l = get_lexeme();
    if (type_ == TokenType::NEWLINE)
    {
      l = "\\n";
    }
    else if (type_ == TokenType::END)
    {
      l = "END";
    }
    std::string out = "<" + tokenTypeStrs[(int)type_] + ", \"" + l + "\"";
    if (type_ == TokenType::DECIMAL || type_ == TokenType::HEX || type_ == TokenType::BINARY)
    {
      out += ", " + std::to_string(value_);
    }
    out += ">";
    return out;
  }
}
