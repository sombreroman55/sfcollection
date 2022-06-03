/*
 *
 *
 *
 *
 *
 */

#include <string>
#include "lexer.hh"

namespace sfas
{
    Lexer::Lexer()  {}
    Lexer::~Lexer() = default;
    std::vector<Token> Lexer::tokenize_line(std::string line, int line_no)
    {
        std::vector<Token> tokens;
        std::string current_lexeme = "";
        LexerState state = line_start;
        int anchor = -1;
        for (int i = 0; i < line.size(); i++)
        {
            switch (state)
            {
                case token_start:
                {
                    anchor = i;
                    switch (line[i])
                    {
                        case ' ':
                        case '\f':
                        case '\t':
                        case '\v':
                            // consume leading whitespace
                            break;

                        case 'a':
                        case 'A':
                            current_lexeme += line[i];
                            state = instruction_a;
                            break;

                        case 'b':
                        case 'B':
                            current_lexeme += line[i];
                            state = instruction_b;
                            break;

                        case 'c':
                        case 'C':
                            current_lexeme += line[i];
                            state = instruction_c;
                            break;

                        case 'd':
                        case 'D':
                            current_lexeme += line[i];
                            state = instruction_d;
                            break;

                        case 'e':
                        case 'E':
                            current_lexeme += line[i];
                            state = instruction_e;
                            break;

                        case 'i':
                        case 'I':
                            current_lexeme += line[i];
                            state = instruction_i;
                            break;

                        case 'j':
                        case 'J':
                            current_lexeme += line[i];
                            state = instruction_j;
                            break;

                        case 'l':
                        case 'L':
                            current_lexeme += line[i];
                            state = instruction_l;
                            break;

                        case 'o':
                        case 'O':
                            current_lexeme += line[i];
                            state = instruction_o;
                            break;

                        case 'p':
                        case 'P':
                            current_lexeme += line[i];
                            state = instruction_p;
                            break;

                        case 'r':
                        case 'R':
                            current_lexeme += line[i];
                            state = instruction_r;
                            break;

                        case 's':
                        case 'S':
                            current_lexeme += line[i];
                            state = instruction_s;
                            break;

                        case 't':
                        case 'T':
                            current_lexeme += line[i];
                            state = instruction_t;
                            break;

                        case 'w':
                        case 'W':
                            current_lexeme += line[i];
                            state = instruction_w;
                            break;

                        case 'x':
                        case 'X':
                            current_lexeme += line[i];
                            state = instruction_x;
                            break;

                        case '#':
                            current_lexeme += line[i];
                            state = number_literal;
                            break;

                        case '$':
                            current_lexeme += line[i];
                            state = address;
                            break;

                        case '.':
                            current_lexeme += line[i];
                            state = directive;
                            break;

                        default:
                            current_lexeme += line[i];
                            state = invalid_token;
                            break;
                    }
                }
                break;

                case invalid_token:
                {
                }
                break;

                case instruction_a:
                {
                    switch (line[i])
                    {
                        case 'd':
                        case 'D':
                            current_lexeme += line[i];
                            state = instruction_ad;
                            break;

                        case 'n':
                        case 'N':
                            current_lexeme += line[i];
                            state = instruction_an;
                            break;

                        case 's':
                        case 'S':
                            current_lexeme += line[i];
                            state = instruction_as;
                            break;
                    }
                }
                break;

                case instruction_ad:
                {
                    if (line[i] == 'c' || line[i] == 'C')
                    {
                        state = instruction_adc;
                    }
                    else
                    {
                        state = invalid_token;
                    }
                    current_lexeme += line[i];
                }
                break;

                case instruction_adc:
                {
                    switch (line[i])
                    {
                        case ' ':
                        case '\f':
                        case '\t':
                        case '\v':
                        {
                            Location loc(line_no, anchor);
                            Token adc_token(TT_ADC, current_lexeme, loc);
                            tokens.push_back(adc_token);
                            current_lexeme.clear();
                            state = token_start;
                        }
                        break;

                        default:
                            state = invalid_token;
                            break;
                    }
                }
                break;

                case instruction_an:
                {
                    if (line[i] == 'd' || line[i] == 'D')
                    {
                        state = instruction_and;
                    }
                    else if (line[i] == ':')
                    {
                        state = identifier;
                    }
                    else
                    {
                        state = invalid_token;
                    }
                    current_lexeme += line[i];
                }
                break;

                case instruction_and:
                {
                    switch (line[i])
                    {
                        case ' ':
                        case '\f':
                        case '\t':
                        case '\v':
                        {
                            Token and_token(TT_AND);
                            tokens.push_back(and_token);
                        }
                        break;

                        default:
                            state = invalid_token;
                            break;
                    }
                }
                break;

                case instruction_as:
                {
                    if (line[i] == 'l' || line[i] == 'L')
                    {
                        state = instruction_asl;
                    }
                    else
                    {
                        state = invalid_token;
                    }
                }
                break;

                case instruction_asl:
                {
                    switch (line[i])
                    {
                        case ' ':
                        case '\f':
                        case '\t':
                        case '\v':
                        {
                            Token asl_token(TT_ASL);
                            tokens.push_back(asl_token);
                        }
                        break;

                        default:
                            state = invalid_token;
                            break;
                    }
                }
                break;
            }
        }
        return tokens;
    }
}
