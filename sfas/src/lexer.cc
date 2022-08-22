/* lexer.cc
 *
 * Lexer/tokenizer
 *
 */

#include <cctype>
#include <string>
#include <vector>
#include "lexer.hh"
#include "location.hh"
#include "token.hh"

namespace sfas
{
  Lexer::Lexer(std::string buffer) : buffer(buffer), state(LexerState::token_start), current_pos(0) {}

  Lexer::~Lexer() = default;

  void Lexer::add_token(TokenType tt)
  {
    std::string lexeme = buffer.substr(anchor, (current_pos - anchor));
    Token t(tt, lexeme);
    /**/ if (tt == TokenType::DECIMAL)
    {
      t.value_ = std::stoul(lexeme.substr(1), nullptr, 10);
    }
    else if (tt == TokenType::HEX)
    {
      t.value_ = std::stoul(lexeme.substr(2), nullptr, 16);
    }
    else if (tt == TokenType::BINARY)
    {
      t.value_ = std::stoul(lexeme.substr(2), nullptr, 2);
    }
    tokens.push_back(t);
    state = LexerState::token_start;
  }

  bool Lexer::is_identifier(char c, bool start)
  {
    if (start) return (c == '_' || isalpha(c));
    else       return (c == '_' || isalnum(c));
  }

  std::vector<Token> Lexer::tokenize()
  {
    while (current_pos < (int)buffer.size())
    {
      char current_char = buffer[current_pos];
      switch (state)
      {
        case LexerState::token_start:
          {
            anchor = current_pos;
            switch (current_char)
            {
              // Consume whitespace
              case ' ':
              case '\t':
              case '\v':
                break;

              // Single character tokens
              case '\n':
                add_token(TokenType::NEWLINE);
                break;

              case '(':
                add_token(TokenType::LPAREN);
                break;

              case ')':
                add_token(TokenType::RPAREN);
                break;

              case '[':
                add_token(TokenType::LSQUARE);
                break;

              case ']':
                add_token(TokenType::RSQUARE);
                break;

              case ',':
                add_token(TokenType::COMMA);
                break;

              // Longer tokens
              case '@':
                state = LexerState::regist;
                break;

              case ';':
                state = LexerState::comment;
                break;

              case '.':
                state = LexerState::directive;
                break;

              case '$':
                state = LexerState::address;
                break;

              case '#':
                state = LexerState::number_literal;
                break;

              default:
                if (is_identifier(current_char, true))
                {
                  state = LexerState::identifier;
                }
                break;
            }
          }
          break;

        case LexerState::regist:
          {
            // TODO
          }
          break;

        case LexerState::address:
          {
            // TODO
          }
          break;

        case LexerState::identifier:
          {
            if (isspace(current_char))
            {
              TokenType tt = TokenType::IDENTIFIER;
              std::string s = buffer.substr(anchor, (current_pos - anchor));
              std::transform(s.begin(), s.end(), s.begin(),
                  [](unsigned char c){ return std::tolower(c); });

              if (keywords.find(s) != keywords.end())
              {
                tt = keywords.at(s);
              }
              add_token(tt);
              --current_pos;
            }
            else if (!is_identifier(current_char, false))
            {
              state = LexerState::invalid;
            }
          }
          break;

        case LexerState::number_literal:
          {
            /**/ if (current_char == '$')
              state = LexerState::hex_number;
            else if (current_char == '%')
              state = LexerState::binary_number;
            else if (isdigit(current_char))
              state = LexerState::decimal_number;
            else
              state = LexerState::invalid;
          }
          break;

        case LexerState::decimal_number:
          {
            if (isspace(current_char))
            {
              add_token(TokenType::DECIMAL);
              --current_pos;
            }
            else if (!isdigit(current_char))
            {
              state = LexerState::invalid;
            }
          }
          break;

        case LexerState::hex_number:
          {
            if (isspace(current_char))
            {
              add_token(TokenType::HEX);
              --current_pos;
            }
            else if (!isxdigit(current_char))
            {
              state = LexerState::invalid;
            }
          }
          break;

        case LexerState::binary_number:
          {
            if (isspace(current_char))
            {
              add_token(TokenType::BINARY);
              --current_pos;
            }
            else if (!(current_char == '0' || current_char == '1'))
            {
              state = LexerState::invalid;
            }
          }
          break;

        case LexerState::comment:
          {
            if (current_char == '\n')
            {
              add_token(TokenType::COMMENT);
              --current_pos;
            }
          }
          break;

        case LexerState::invalid:
          {
            if (isspace(current_char))
            {
              add_token(TokenType::ERROR);
              --current_pos;
            }
          }
          break;

        default:
          break;
      }
      current_pos++;
    }

    Token t(TokenType::END, "\0");
    tokens.push_back(t);

    return tokens;
  }
}
