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
  Lexer::Lexer() {}

  Lexer::~Lexer() = default;

  std::vector<Token> Lexer::tokenize_buffer(std::string buffer)
  {
    std::vector<Token> tokens;
    LexerState state = LexerState::token_start;
    int anchor = -1;
    for (int i = 0; i < (int)buffer.size(); i++)
    {
      char current_char = buffer[i];
      switch (state)
      {
        case LexerState::token_start:
          {
            // Consume whitespace before switch case
            // If not whitespace, pin anchor
            anchor = i;
            switch (current_char)
            {
              case ';':
                state = LexerState::comment;
                break;

              case '\n':
                {
                  Token t(TokenType::TT_NEWLINE, "\n");
                  tokens.push_back(t);
                }
                break;

              case '#':
                state = LexerState::number_literal;
                break;

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
            if (!isdigit(current_char))
            {
              if (isspace(current_char))
              {
                std::string lexeme = buffer.substr(anchor, (i-anchor));
                Token t(TokenType::TT_NUMBER, lexeme);
                tokens.push_back(t);
                state = LexerState::token_start;
                i--;
                break;
              }
              else
              {
                state = LexerState::invalid;
              }
            }
          }
          break;

        case LexerState::hex_number:
          {
            if (!isxdigit(current_char))
            {
              if (isspace(current_char))
              {
                std::string lexeme = buffer.substr(anchor, (i-anchor));
                Token t(TokenType::TT_NUMBER, lexeme);
                tokens.push_back(t);
                state = LexerState::token_start;
                i--;
                break;
              }
              else
              {
                state = LexerState::invalid;
              }
            }
          }
          break;

        case LexerState::binary_number:
          {
            if (!(current_char == '0' || current_char == '1'))
            {
              if (isspace(current_char))
              {
                std::string lexeme = buffer.substr(anchor, (i-anchor));
                Token t(TokenType::TT_NUMBER, lexeme);
                tokens.push_back(t);
                state = LexerState::token_start;
                i--;
                break;
              }
              else
              {
                state = LexerState::invalid;
              }
            }
          }
          break;

        case LexerState::comment:
          {
            if (current_char == '\n')
            {
              std::string lexeme = buffer.substr(anchor, (i-anchor));
              Token t(TokenType::TT_COMMENT, lexeme);
              tokens.push_back(t);
              state = LexerState::token_start;
              i--;
              break;
            }
          }
          break;

        case LexerState::invalid:
          {
            if (isspace(current_char))
            {
              std::string lexeme = buffer.substr(anchor, (i-anchor));
              Token t(TokenType::TT_ERROR, lexeme);
              tokens.push_back(t);
              state = LexerState::token_start;
              i--;
              break;
            }
          }
          break;

        default:
          break;
      }
    }

    Token t(TokenType::TT_EOF, "\0");
    tokens.push_back(t);

    return tokens;
  }
}
