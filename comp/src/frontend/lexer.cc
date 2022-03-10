/* lexer.cc
 *
 * Lexer
 */

#include "lexer.hh"
#include "token.hh"

using SFCC::DataStructures::Token;
using SFCC::DataStructures::TokenType;

namespace SFCC
{
    namespace Frontend
    {
        Lexer::Lexer()
        {
        }

        std::vector<SFCC::DataStructures::Token> Lexer::lex(void)
        {
            std::vector<SFCC::DataStructures::Token> tokenStream;
        }

        SFCC::DataStructures::Token Lexer::getNextToken(char* p)
        {
            char* anchor = p;
            char lexchr;
            switch(lexchr = *p)
            {
                case 0x00:        goto end;

                /*
                case 0x08:
                case '\t':
                case '\v':
                case '\f':
                case ' ':         goto whitespace;

                case '\n':        goto newline;
                case '\r':        goto creturn;

                case '!':         goto bang;
                case '"':         goto quote;
                case '&':         goto and;
                case '+':         goto plus;
                case '-':         goto minus;
                case '/':         goto div;

                case '0' ... '9': goto constant;

                case 'A' ... 'Z':
                case 'h':
                case 'j' ... 'k':
                case 'm' ... 'q':
                case 'x' ... 'z': goto id_advance;
                */

                case 'a':         goto a_group;
                case 'b':         goto b_group;
                case 'c':         goto c_group;
                case 'd':         goto d_group;
                case 'e':         goto e_group;
                case 'f':         goto f_group;
                case 'g':         goto g_group;
                case 'i':         goto i_group;
                case 'l':         goto l_group;
                case 'r':         goto r_group;
                case 's':         goto s_group;
                case 't':         goto t_group;
                case 'u':         goto u_group;
                case 'v':         goto v_group;
                case 'w':         goto w_group;
                case '_':         goto under_group;

                default:          goto single_char;
            }
end:            { return Token(std::string(), TokenType::none); }
single_char:    {
                    // TODO
                }
id_advance:     lexchr = *++p;
id_loop:        switch(lexchr = *++p)
                {
                    case '0' ... '9':
                    case 'A' ... 'Z':
                    case '_':
                    case 'a' ... 'z': goto id_advance;
                    default: { return Token(std::string(anchor, p), TokenType::identifier); }
                }

a_group:        if ((lexchr = *++p) == 'u') goto auto_t;     goto id_advance;
auto_t:         if ((lexchr = *++p) == 't') goto auto_o;     goto id_advance;
auto_o:         if ((lexchr = *++p) == 'o') goto auto_sink;  goto id_advance;
auto_sink:      switch(lexchr = *++p)
                {
                    case '0' ... '9':
                    case 'A' ... 'Z':
                    case '_':
                    case 'a' ... 'z': goto id_advance;
                    default: { return Token(std::string(anchor, p), TokenType::keyword); }
                }

b_group:        if ((lexchr = *++p) == 'r') goto break_e;    goto id_advance;
break_e:        if ((lexchr = *++p) == 'e') goto break_a;    goto id_advance;
break_a:        if ((lexchr = *++p) == 'a') goto break_k;    goto id_advance;
break_k:        if ((lexchr = *++p) == 'k') goto break_sink; goto id_advance;
break_sink:     switch(lexchr = *++p)
                {
                    case '0' ... '9':
                    case 'A' ... 'Z':
                    case '_':
                    case 'a' ... 'z': goto id_advance;
                    default: { return Token(std::string(anchor, p), TokenType::keyword); }
                }

c_group:        switch(lexchr = *++p)
                {
                    case 'a': goto case_s;
                    case 'h': goto char_a;
                    case 'o': goto con_n;
                    default:  goto id_advance;
                }
case_s:
case_e:
case_sink:      switch(lexchr = *++p)
                {
                    case '0' ... '9':
                    case 'A' ... 'Z':
                    case '_':
                    case 'a' ... 'z': goto id_advance;
                    default: { return Token(std::string(anchor, p), TokenType::keyword); }
                }

d_group:

e_group:

f_group:

g_group:

i_group:

l_group:

r_group:

s_group:

t_group:

u_group:

v_group:
vo_o:
void_i:
void_d:
void_sink:

volatile_l1:
volatile_a:
volatile_t:
volatile_i:
volatile_l2:
volatile_e:
volatile_sink:  switch(lexchr = *++p)
                {
                    case '0' ... '9':
                    case 'A' ... 'Z':
                    case '_':
                    case 'a' ... 'z': goto id_advance;
                    default: { ; }
                }

w_group:

under_group:
bool_o1:
bool_o2:
bool_l:
bool_sink:

complex_o:
complex_m:
complex_p:
complex_l:
complex_e:
complex_x:
complex_sink:

imaginary_m:
imaginary_a1:
imaginary_g:
imaginary_i:
imaginary_n:
imaginary_a2:
imaginary_r:
imaginary_y:
imaginary_sink: return Token("", TokenType::none);
        }
    }
}
