/*
 *
 *
 *
 *
 *
 */

#include <string>
#include <vector>
#include "lexer.hh"
#include "location.hh"

namespace sfas
{
    Lexer::Lexer()  {}
    Lexer::~Lexer() = default;
    std::vector<Token> Lexer::tokenize_line(std::string line, int line_no)
    {
        std::vector<Token> tokens;
        std::string current_lexeme = "";
        LexerState state = LexerState::token_start;
        int anchor = -1;
        for (int i = 0; i < line.size(); i++)
        {
            switch (state)
            {
                case LexerState::token_start:
                {
                    anchor = i;
                    switch (line[i])
                    {
                        case EOF:
                            break;

                        case ' ':
                        case '\f':
                        case '\t':
                        case '\v':
                            // consume leading whitespace
                            break;

                        case 'a':
                        case 'A':
                            current_lexeme += line[i];
                            state = LexerState::instruction_a;
                            break;

                        case 'b':
                        case 'B':
                            current_lexeme += line[i];
                            state = LexerState::instruction_b;
                            break;

                        case 'c':
                        case 'C':
                            current_lexeme += line[i];
                            state = LexerState::instruction_c;
                            break;

                        case 'd':
                        case 'D':
                            current_lexeme += line[i];
                            state = LexerState::instruction_d;
                            break;

                        case 'e':
                        case 'E':
                            current_lexeme += line[i];
                            state = LexerState::instruction_e;
                            break;

                        case 'i':
                        case 'I':
                            current_lexeme += line[i];
                            state = LexerState::instruction_i;
                            break;

                        case 'j':
                        case 'J':
                            current_lexeme += line[i];
                            state = LexerState::instruction_j;
                            break;

                        case 'l':
                        case 'L':
                            current_lexeme += line[i];
                            state = LexerState::instruction_l;
                            break;

                        case 'o':
                        case 'O':
                            current_lexeme += line[i];
                            state = LexerState::instruction_o;
                            break;

                        case 'p':
                        case 'P':
                            current_lexeme += line[i];
                            state = LexerState::instruction_p;
                            break;

                        case 'r':
                        case 'R':
                            current_lexeme += line[i];
                            state = LexerState::instruction_r;
                            break;

                        case 's':
                        case 'S':
                            current_lexeme += line[i];
                            state = LexerState::instruction_s;
                            break;

                        case 't':
                        case 'T':
                            current_lexeme += line[i];
                            state = LexerState::instruction_t;
                            break;

                        case 'w':
                        case 'W':
                            current_lexeme += line[i];
                            state = LexerState::instruction_w;
                            break;

                        case 'x':
                        case 'X':
                            current_lexeme += line[i];
                            state = LexerState::instruction_x;
                            break;

                        case '#':
                            current_lexeme += line[i];
                            state = LexerState::number_literal;
                            break;

                        case '$':
                            current_lexeme += line[i];
                            state = LexerState::address;
                            break;

                        case '.':
                            current_lexeme += line[i];
                            state = LexerState::directive;
                            break;

                        default:
                            current_lexeme += line[i];
                            state = LexerState::invalid_token;
                            break;
                    }
                }
                break;

                case LexerState::invalid_token:
                {
                }
                break;

                case LexerState::instruction_a:
                {
                    switch (line[i])
                    {
                        case 'd':
                        case 'D':
                            current_lexeme += line[i];
                            state = LexerState::instruction_ad;
                            break;

                        case 'n':
                        case 'N':
                            current_lexeme += line[i];
                            state = LexerState::instruction_an;
                            break;

                        case 's':
                        case 'S':
                            current_lexeme += line[i];
                            state = LexerState::instruction_as;
                            break;
                    }
                }
                break;

                case LexerState::instruction_ad:
                {
                    if (line[i] == 'c' || line[i] == 'C')
                    {
                        state = LexerState::instruction_adc;
                    }
                    else
                    {
                        state = LexerState::invalid_token;
                    }
                    current_lexeme += line[i];
                }
                break;

                case LexerState::instruction_adc:
                {
                    switch (line[i])
                    {
                        case ' ':
                        case '\f':
                        case '\t':
                        case '\v':
                        {
                            Location loc(line_no, anchor);
                            Token adc_token(Token::TT_ADC, current_lexeme, loc);
                            tokens.push_back(adc_token);
                            current_lexeme.clear();
                            state = LexerState::token_start;
                        }
                        break;

                        default:
                            state = LexerState::invalid_token;
                            break;
                    }
                }
                break;

                case LexerState::instruction_an:
                {
                    if (line[i] == 'd' || line[i] == 'D')
                    {
                        state = LexerState::instruction_and;
                    }
                    else if (line[i] == ':')
                    {
                        state = LexerState::identifier;
                    }
                    else
                    {
                        state = LexerState::invalid_token;
                    }
                    current_lexeme += line[i];
                }
                break;

                case LexerState::instruction_and:
                {
                    switch (line[i])
                    {
                        case ' ':
                        case '\f':
                        case '\t':
                        case '\v':
                        {
                            // Token and_token(Token::TT_AND);
                            // tokens.push_back(and_token);
                        }
                        break;

                        default:
                            state = LexerState::invalid_token;
                            break;
                    }
                }
                break;

                case LexerState::instruction_as:
                {
                    if (line[i] == 'l' || line[i] == 'L')
                    {
                        state = LexerState::instruction_asl;
                    }
                    else
                    {
                        state = LexerState::invalid_token;
                    }
                }
                break;

                case LexerState::instruction_asl:
                {
                    switch (line[i])
                    {
                        case ' ':
                        case '\f':
                        case '\t':
                        case '\v':
                        {
                            // Token asl_token(Token::TT_ASL);
                            // tokens.push_back(asl_token);
                        }
                        break;

                        default:
                            state = LexerState::invalid_token;
                            break;
                    }
                }
                break;
            }
        }
        return tokens;
    }
}
