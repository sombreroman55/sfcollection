/* lexer.cc
 *
 * Lexer
 */

#define TOKEN_SINK(token_type) \
                switch(lexchr = *++p)\
                {\
                    case '0' ... '9':\
                    case 'A' ... 'Z':\
                    case '_':\
                    case 'a' ... 'z': goto id_advance;\
                    default: { return #token_type; }\
                }


#include "lexer.hh"
#include "token.hh"
using namespace SFCC::Frontend;

SFCC::DataStructures::Token Lexer::getNextToken(char* p)
{
    char lexchr;
    switch(lexchr = *p)
    {
        case 0x00:        goto end;
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

        case 'h':
        case 'j' ... 'k':
        case 'm' ... 'q':
        case 'x' ... 'z':
        case 'A' ... 'Z': goto id_advance;

        default:          return;
    }
end:            { return "end"; }
id_advance:     lexchr = *++p;
id_loop:        switch(lexchr == *++p)
                {
                    case '0' ... '9':
                    case 'A' ... 'Z':
                    case '_':
                    case 'a' ... 'z': goto id_advance;
                    default: { return "ident"; }
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
                    default: { return "auto"; }
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
                    default: { return "break"; }
                }

v_group:
vo_o:
void_i:
void_d:
void_sink:

volatile_l:
volatile_a:
volatile_t:
volatile_i:
volatile_l:
volatile_e:
volatile_sink:  switch(lexchr = *++p)
                {
                    case '0' ... '9':
                    case 'A' ... 'Z':
                    case '_':
                    case 'a' ... 'z': goto id_advance;
                    default: { return "volatile"; }
                }

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
imaginary_a:
imaginary_g:
imaginary_i:
imaginary_n:
imaginary_a:
imaginary_r:
imaginary_y:
imaginary_sink: SINK_STATE(imaginary)
}
