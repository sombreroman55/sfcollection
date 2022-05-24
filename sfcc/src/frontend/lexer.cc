/* lexer.cc
 *
 * Lexer
 */

#include "lexer.hh"
#include "token.hh"

using SFCC::DataStructures::Location;
using SFCC::DataStructures::Token;
using SFCC::DataStructures::TokenType;

static constexpr Location loc =
{
    .line = 1, .col = 1
};

namespace SFCC
{
    namespace Frontend
    {
        Lexer::Lexer(std::string filename, std::string buffer)
            : _filename(filename)
            , _buffer(buffer)
        {
        }

        std::vector<SFCC::DataStructures::Token> Lexer::lex(void)
        {
            std::vector<SFCC::DataStructures::Token> tokenStream;
            tokenStream.push_back(_getNextToken(_buffer.c_str()));
            return tokenStream;
        }

        SFCC::DataStructures::Token Lexer::_getNextToken(const char* p)
        {
            const char* anchor = p;
            char lexchr;
start:
            switch (lexchr = *p)
            {
                case 0x00:        goto end;

                case 0x08:
                case '\t':
                case '\v':
                case '\f':
                case ' ':         goto keep_going;

                case '\n':        goto newline;
                case '\r':        goto creturn;

                case '!':         goto bang;
                case '"':         goto quote;
                case '&':         goto _and;
                case '+':         goto plus;
                case '-':         goto minus;
                case '/':         goto div;

                case '0' ... '9': goto constant;

                case 'A' ... 'Z':
                case 'h':
                case 'j' ... 'k':
                case 'm' ... 'q':
                case 'x' ... 'z': goto id_advance;

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

newline:
creturn:        /* TODO: increase line count */
keep_going:     lexchr = *++p; goto start;
end:            { return Token(TokenType::INTERNAL_EOF, loc); }

// --------------------------------------------------------------------------------
// PUNCTUATORS
// --------------------------------------------------------------------------------
single_char:    {
                    switch (lexchr)
                    {
                        case '[':   return Token(TokenType::PUNC_LSQUARE,   loc);
                        case ']':   return Token(TokenType::PUNC_RSQUARE,   loc);
                        case '(':   return Token(TokenType::PUNC_LPAREN,    loc);
                        case ')':   return Token(TokenType::PUNC_RPAREN,    loc);
                        case '{':   return Token(TokenType::PUNC_LCURLY,    loc);
                        case '}':   return Token(TokenType::PUNC_RCURLY,    loc);
                        case '.':   return Token(TokenType::PUNC_DOT,       loc);
                        case '~':   return Token(TokenType::PUNC_TILDE,     loc);
                        case ':':   return Token(TokenType::PUNC_COLON,     loc);
                        case ';':   return Token(TokenType::PUNC_SEMICOLON, loc);
                        case ',':   return Token(TokenType::PUNC_COMMA,     loc);
                        default:    return Token(TokenType::INTERNAL_ERROR, loc);
                    }
                }
bang:           if ((lexchr = *++p) == '=') return Token(TokenType::PUNC_NEQ,  loc);
                else                        return Token(TokenType::PUNC_BANG, loc);

quote:          if ((lexchr = *++p) == '=') return Token(TokenType::PUNC_NEQ,  loc);
                else                        return Token(TokenType::PUNC_BANG, loc);

_and:           if ((lexchr = *++p) == '=') return Token(TokenType::PUNC_NEQ,  loc);
                else                        return Token(TokenType::PUNC_BANG, loc);

plus:           if ((lexchr = *++p) == '=') return Token(TokenType::PUNC_NEQ,  loc);
                else                        return Token(TokenType::PUNC_BANG, loc);

minus:          if ((lexchr = *++p) == '=') return Token(TokenType::PUNC_NEQ,  loc);
                else                        return Token(TokenType::PUNC_BANG, loc);

div:            switch (lexchr = *++p)
                {
                    case '=': return Token(TokenType::PUNC_RMW_DIV, loc);
                    case '*': goto ansi_comment;
                    case '/': goto line_comment;
                    default:  return Token(TokenType::PUNC_DIV, loc);
                }

ansi_comment1:   switch (lexchr = *++p)
                {
                    case '*':  goto ansi_comment_close;
                    case '\r': goto keep_going;
                    default:   goto ansi_comment;
                }
ansi_comment_close: if ((lexchr = *++p) == '/') return Token(TokenType::PUNC_NEQ,  loc);

line_comment:       switch (lexchr = *++p)
                    {
                        case '\n':
                        case '\r': goto keep_going;
                        default:   goto line_comment;
                    }

// --------------------------------------------------------------------------------
// CONSTANT
// --------------------------------------------------------------------------------
int_constant:       switch (lexchr = *++p)
                    {
                        case '.':         goto float_constant;
                        case '0' ... '9': goto int_constant;
                        default:          return Token(TokenType::CONSTANT_INT, loc);
                    }

float_constant:     switch (lexchr = *++p)
                    {
                        case '0' ... '9': goto float_constant;
                        default:          return Token(TokenType::CONSTANT_INT, loc);
                    }

// --------------------------------------------------------------------------------
// IDENTIFIER
// --------------------------------------------------------------------------------
id_advance:         lexchr = *++p;
id_loop:            switch (lexchr)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::IDENTIFIER, loc, std::string(anchor, lexchr)); }
                    }

// --------------------------------------------------------------------------------
// A GROUP
// --------------------------------------------------------------------------------
a_group:            if ((lexchr = *++p) == 'u') goto auto_t;            goto id_loop;
auto_t:             if ((lexchr = *++p) == 't') goto auto_o;            goto id_loop;
auto_o:             if ((lexchr = *++p) == 'o') goto auto_sink;         goto id_loop;
auto_sink:          switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_AUTO, loc); }
                    }

// --------------------------------------------------------------------------------
// B GROUP
// --------------------------------------------------------------------------------
b_group:            if ((lexchr = *++p) == 'r') goto break_e;           goto id_loop;
break_e:            if ((lexchr = *++p) == 'e') goto break_a;           goto id_loop;
break_a:            if ((lexchr = *++p) == 'a') goto break_k;           goto id_loop;
break_k:            if ((lexchr = *++p) == 'k') goto break_sink;        goto id_loop;
break_sink:         switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_BREAK, loc); }
                    }

// --------------------------------------------------------------------------------
// C GROUP
// --------------------------------------------------------------------------------
c_group:            switch (lexchr = *++p)
                    {
                        case 'a': goto case_s;
                        case 'h': goto char_a;
                        case 'o': goto co_group;
                        default:  goto id_loop;
                    }
case_s:             if ((lexchr = *++p) == 's') goto case_e;            goto id_loop;
case_e:             if ((lexchr = *++p) == 'e') goto case_sink;         goto id_loop;
case_sink:          switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_CASE, loc); }
                    }

char_a:             if ((lexchr = *++p) == 'a') goto char_r;            goto id_loop;
char_r:             if ((lexchr = *++p) == 'r') goto char_sink;         goto id_loop;
char_sink:          switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_CHAR, loc); }
                    }

co_group:           if ((lexchr = *++p) == 'n') goto con_group;         goto id_loop;
con_group:          switch (lexchr = *++p)
                    {
                        case 's': goto const_t;
                        case 't': goto continue_i;
                        default:  goto id_loop;
                    }

const_t:            if ((lexchr = *++p) == 't') goto const_sink;        goto id_loop;
const_sink:         switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_CONST, loc); }
                    }

continue_i:         if ((lexchr = *++p) == 'i') goto continue_n;        goto id_loop;
continue_n:         if ((lexchr = *++p) == 'n') goto continue_u;        goto id_loop;
continue_u:         if ((lexchr = *++p) == 'u') goto continue_e;        goto id_loop;
continue_e:         if ((lexchr = *++p) == 'e') goto continue_sink;     goto id_loop;
continue_sink:      switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_CONTINUE, loc); }
                    }

// --------------------------------------------------------------------------------
// D GROUP
// --------------------------------------------------------------------------------
d_group:            if ((lexchr = *++p) == 'o') goto do_sink;           goto id_loop;
do_sink:            switch (lexchr = *++p)
                    {
                        case 'u': goto double_b;
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 't':
                        case 'v' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_DO, loc); }
                    }

double_b:           if ((lexchr = *++p) == 'b') goto double_l;          goto id_loop;
double_l:           if ((lexchr = *++p) == 'l') goto double_e;          goto id_loop;
double_e:           if ((lexchr = *++p) == 'e') goto double_sink;       goto id_loop;
double_sink:        switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_DOUBLE, loc); }
                    }

// --------------------------------------------------------------------------------
// E GROUP
// --------------------------------------------------------------------------------
e_group:            switch (lexchr = *++p)
                    {
                        case 'l': goto else_s;
                        case 'n': goto _enum_u;
                        case 'x': goto extern_t;
                        default:  goto id_loop;
                    }
else_s:             if ((lexchr = *++p) == 's') goto else_s;            goto id_loop;
else_e:             if ((lexchr = *++p) == 'e') goto else_sink;         goto id_loop;
else_sink:          switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_ELSE, loc); }
                    }

_enum_u:            if ((lexchr = *++p) == 'u') goto _enum_u;           goto id_loop;
_enum_m:            if ((lexchr = *++p) == 'm') goto _enum_sink;        goto id_loop;
_enum_sink:         switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_ENUM, loc); }
                    }

extern_t:           if ((lexchr = *++p) == 't') goto extern_e;          goto id_loop;
extern_e:           if ((lexchr = *++p) == 'e') goto extern_r;          goto id_loop;
extern_r:           if ((lexchr = *++p) == 'r') goto extern_n;          goto id_loop;
extern_n:           if ((lexchr = *++p) == 'n') goto extern_sink;       goto id_loop;
extern_sink:        switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_EXTERN, loc); }
                    }

// --------------------------------------------------------------------------------
// F GROUP
// --------------------------------------------------------------------------------
f_group:            switch (lexchr = *++p)
                    {
                        case 'l': goto float_o;
                        case 'o': goto for_r;
                        default:  goto id_loop;
                    }

float_o:            if ((lexchr = *++p) == 'o') goto float_a;           goto id_loop;
float_a:            if ((lexchr = *++p) == 'a') goto float_t;           goto id_loop;
float_t:            if ((lexchr = *++p) == 't') goto float_sink;        goto id_loop;
float_sink:         switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_FLOAT, loc); }
                    }

for_r:              if ((lexchr = *++p) == 'r') goto for_sink;          goto id_loop;
for_sink:           switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_FOR, loc); }
                    }

// --------------------------------------------------------------------------------
// G GROUP
// --------------------------------------------------------------------------------
g_group:            if ((lexchr = *++p) == 'o') goto goto_t;            goto id_loop;
goto_t:             if ((lexchr = *++p) == 't') goto goto_o;            goto id_loop;
goto_o:             if ((lexchr = *++p) == 'o') goto goto_sink;         goto id_loop;
goto_sink:          switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_GOTO, loc); }
                    }

// --------------------------------------------------------------------------------
// I GROUP
// --------------------------------------------------------------------------------
i_group:            switch (lexchr = *++p)
                    {
                        case 'f': goto if_sink;
                        case 'n': goto in_group;
                        default:  goto id_loop;
                    }

if_sink:            switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_IF, loc); }
                    }

in_group:           switch (lexchr = *++p)
                    {
                        case 'l': goto inline_i;
                        case 't': goto int_sink;
                        default:  goto id_loop;
                    }

inline_i:           if ((lexchr = *++p) == 'i') goto inline_n;          goto id_loop;
inline_n:           if ((lexchr = *++p) == 'n') goto inline_e;          goto id_loop;
inline_e:           if ((lexchr = *++p) == 'e') goto inline_sink;       goto id_loop;
inline_sink:        switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_INLINE, loc); }
                    }

int_sink:           switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_INT, loc); }
                    }

// --------------------------------------------------------------------------------
// L GROUP
// --------------------------------------------------------------------------------
l_group:            if ((lexchr = *++p) == 'o') goto long_n;            goto id_loop;
long_n:             if ((lexchr = *++p) == 'n') goto long_g;            goto id_loop;
long_g:             if ((lexchr = *++p) == 'g') goto long_sink;         goto id_loop;
long_sink:          switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_LONG, loc); }
                    }

// --------------------------------------------------------------------------------
// R GROUP
// --------------------------------------------------------------------------------
r_group:            if ((lexchr = *++p) == 'e') goto re_group;          goto id_loop;
re_group:           switch (lexchr = *++p)
                    {
                        case 'g': goto register_i;
                        case 's': goto restrict_t1;
                        case 't': goto return_u;
                        default:  goto id_loop;
                    }

register_i:         if ((lexchr = *++p) == 'i') goto register_s;        goto id_loop;
register_s:         if ((lexchr = *++p) == 's') goto register_t;        goto id_loop;
register_t:         if ((lexchr = *++p) == 't') goto register_e;        goto id_loop;
register_e:         if ((lexchr = *++p) == 'e') goto register_r;        goto id_loop;
register_r:         if ((lexchr = *++p) == 'r') goto register_sink;     goto id_loop;
register_sink:      switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_REGISTER, loc); }
                    }

restrict_t1:        if ((lexchr = *++p) == 't') goto restrict_r;        goto id_loop;
restrict_r:         if ((lexchr = *++p) == 'r') goto restrict_i;        goto id_loop;
restrict_i:         if ((lexchr = *++p) == 'i') goto restrict_c;        goto id_loop;
restrict_c:         if ((lexchr = *++p) == 'c') goto restrict_t2;       goto id_loop;
restrict_t2:        if ((lexchr = *++p) == 't') goto restrict_sink;     goto id_loop;
restrict_sink:      switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_RESTRICT, loc); }
                    }

return_u:           if ((lexchr = *++p) == 'u') goto return_r;          goto id_loop;
return_r:           if ((lexchr = *++p) == 'r') goto return_n;          goto id_loop;
return_n:           if ((lexchr = *++p) == 'n') goto return_sink;       goto id_loop;
return_sink:        switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_RETURN, loc); }
                    }

// --------------------------------------------------------------------------------
// S GROUP
// --------------------------------------------------------------------------------
s_group:            switch (lexchr = *++p)
                    {
                        case 'h': goto short_o;
                        case 'i': goto si_i;
                        case 't': goto st_t;
                        case 'w': goto switch_i;
                        default:  goto id_loop;
                    }

short_o:            if ((lexchr = *++p) == 'o') goto short_r;           goto id_loop;
short_r:            if ((lexchr = *++p) == 'r') goto short_t;           goto id_loop;
short_t:            if ((lexchr = *++p) == 't') goto short_sink;        goto id_loop;
short_sink:         switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_SHORT, loc); }
                    }

si_i:               switch (lexchr = *++p)
                    {
                        case 'g': goto signed_g;
                        case 'z': goto sizeof_z;
                        default:  goto id_loop;
                    }

signed_g:           if ((lexchr = *++p) == 'g') goto signed_n;          goto id_loop;
signed_n:           if ((lexchr = *++p) == 'n') goto signed_e;          goto id_loop;
signed_e:           if ((lexchr = *++p) == 'e') goto signed_d;          goto id_loop;
signed_d:           if ((lexchr = *++p) == 'd') goto signed_sink;       goto id_loop;
signed_sink:        switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_SIGNED, loc); }
                    }

sizeof_z:           if ((lexchr = *++p) == 'z') goto sizeof_e;          goto id_loop;
sizeof_e:           if ((lexchr = *++p) == 'e') goto sizeof_o;          goto id_loop;
sizeof_o:           if ((lexchr = *++p) == 'o') goto sizeof_f;          goto id_loop;
sizeof_f:           if ((lexchr = *++p) == 'f') goto sizeof_sink;       goto id_loop;
sizeof_sink:        switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_SIZEOF, loc); }
                    }

st_t:               switch (lexchr = *++p)
                    {
                        case 't': goto static_a;
                        case 'r': goto _struct_u;
                        default:  goto id_loop;
                    }

static_a:           if ((lexchr = *++p) == 'a') goto static_t;          goto id_loop;
static_t:           if ((lexchr = *++p) == 't') goto static_i;          goto id_loop;
static_i:           if ((lexchr = *++p) == 'i') goto static_c;          goto id_loop;
static_c:           if ((lexchr = *++p) == 'c') goto static_sink;       goto id_loop;
static_sink:        switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_STATIC, loc); }
                    }

_struct_r:          if ((lexchr = *++p) == 'r') goto _struct_u;         goto id_loop;
_struct_u:          if ((lexchr = *++p) == 'u') goto _struct_c;         goto id_loop;
_struct_c:          if ((lexchr = *++p) == 'c') goto _struct_t;         goto id_loop;
_struct_t:          if ((lexchr = *++p) == 't') goto _struct_sink;      goto id_loop;
_struct_sink:       switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_STRUCT, loc); }
                    }

switch_i:           if ((lexchr = *++p) == 'i') goto switch_t;          goto id_loop;
switch_t:           if ((lexchr = *++p) == 't') goto switch_c;          goto id_loop;
switch_c:           if ((lexchr = *++p) == 'c') goto switch_h;          goto id_loop;
switch_h:           if ((lexchr = *++p) == 'h') goto switch_sink;       goto id_loop;
switch_sink:        switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_SWITCH, loc); }
                    }

// --------------------------------------------------------------------------------
// T GROUP
// --------------------------------------------------------------------------------
t_group:            if ((lexchr = *++p) == 'y') goto typedef_p;         goto id_loop;
typedef_p:          if ((lexchr = *++p) == 'p') goto typedef_e1;        goto id_loop;
typedef_e1:         if ((lexchr = *++p) == 'e') goto typedef_d;         goto id_loop;
typedef_d:          if ((lexchr = *++p) == 'd') goto typedef_e2;        goto id_loop;
typedef_e2:         if ((lexchr = *++p) == 'e') goto typedef_f;         goto id_loop;
typedef_f:          if ((lexchr = *++p) == 'f') goto typedef_sink;      goto id_loop;
typedef_sink:       switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_TYPEDEF, loc); }
                    }

// --------------------------------------------------------------------------------
// U GROUP
// --------------------------------------------------------------------------------
u_group:            if ((lexchr = *++p) == 'n') goto un_n;              goto id_loop;
un_n:               switch (lexchr = *++p)
                    {
                        case 'i': goto void_i;
                        case 's': goto volatile_a;
                        default:  goto id_loop;
                    }

union_i:            if ((lexchr = *++p) == 'i') goto void_d;            goto id_loop;
union_o:            if ((lexchr = *++p) == 'd') goto void_sink;         goto id_loop;
union_n:            if ((lexchr = *++p) == 'd') goto void_sink;         goto id_loop;
union_sink:         switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_UNION, loc); }
                    }

unsigned_s:         if ((lexchr = *++p) == 's') goto unsigned_i;        goto id_loop;
unsigned_i:         if ((lexchr = *++p) == 'i') goto unsigned_g;        goto id_loop;
unsigned_g:         if ((lexchr = *++p) == 'g') goto unsigned_n;        goto id_loop;
unsigned_n:         if ((lexchr = *++p) == 'n') goto unsigned_e;        goto id_loop;
unsigned_e:         if ((lexchr = *++p) == 'e') goto unsigned_d;        goto id_loop;
unsigned_d:         if ((lexchr = *++p) == 'd') goto unsigned_sink;     goto id_loop;
unsigned_sink:      switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_UNSIGNED, loc); }
                    }

// --------------------------------------------------------------------------------
// V GROUP
// --------------------------------------------------------------------------------
v_group:            if ((lexchr = *++p) == 'o') goto vo_o;              goto id_loop;
vo_o:               switch (lexchr = *++p)
                    {
                        case 'i': goto void_i;
                        case 'l': goto volatile_a;
                        default:  goto id_loop;
                    }

void_i:             if ((lexchr = *++p) == 'i') goto void_d;            goto id_loop;
void_d:             if ((lexchr = *++p) == 'd') goto void_sink;         goto id_loop;
void_sink:          switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_VOID, loc); }
                    }

volatile_a:         if ((lexchr = *++p) == 'a') goto volatile_t;        goto id_loop;
volatile_t:         if ((lexchr = *++p) == 't') goto volatile_i;        goto id_loop;
volatile_i:         if ((lexchr = *++p) == 'i') goto volatile_l;        goto id_loop;
volatile_l:         if ((lexchr = *++p) == 'l') goto volatile_e;        goto id_loop;
volatile_e:         if ((lexchr = *++p) == 'e') goto volatile_sink;     goto id_loop;
volatile_sink:      switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_VOLATILE, loc); }
                    }

// --------------------------------------------------------------------------------
// W GROUP
// --------------------------------------------------------------------------------
w_group:            if ((lexchr = *++p) == 'h') goto while_i;           goto id_loop;
while_i:            if ((lexchr = *++p) == 'i') goto while_l;           goto id_loop;
while_l:            if ((lexchr = *++p) == 'l') goto while_e;           goto id_loop;
while_e:            if ((lexchr = *++p) == 'e') goto while_sink;        goto id_loop;
while_sink:         switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_WHILE, loc); }
                    }

// --------------------------------------------------------------------------------
// UNDERSCORE GROUP
// --------------------------------------------------------------------------------
under_group:        switch (lexchr = *++p)
                    {
                        case 'B': goto Bool_o1;
                        case 'C': goto Complex_o;
                        case 'I': goto Imaginary_m;
                        default:  goto id_loop;
                    }

Bool_o1:            if ((lexchr = *++p) == 'o') goto Bool_o2;           goto id_loop;
Bool_o2:            if ((lexchr = *++p) == 'o') goto Bool_l;            goto id_loop;
Bool_l:             if ((lexchr = *++p) == 'l') goto Bool_sink;         goto id_loop;
Bool_sink:          switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_BOOL_, loc); }
                    }

Complex_o:          if ((lexchr = *++p) == 'o') goto Complex_m;         goto id_loop;
Complex_m:          if ((lexchr = *++p) == 'm') goto Complex_p;         goto id_loop;
Complex_p:          if ((lexchr = *++p) == 'p') goto Complex_l;         goto id_loop;
Complex_l:          if ((lexchr = *++p) == 'l') goto Complex_e;         goto id_loop;
Complex_e:          if ((lexchr = *++p) == 'e') goto Complex_x;         goto id_loop;
Complex_x:          if ((lexchr = *++p) == 'x') goto Complex_sink;      goto id_loop;
Complex_sink:       switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_COMPLEX_, loc); }
                    }

Imaginary_m:        if ((lexchr = *++p) == 'm') goto Imaginary_a1;      goto id_loop;
Imaginary_a1:       if ((lexchr = *++p) == 'a') goto Imaginary_g;       goto id_loop;
Imaginary_g:        if ((lexchr = *++p) == 'g') goto Imaginary_i;       goto id_loop;
Imaginary_i:        if ((lexchr = *++p) == 'i') goto Imaginary_n;       goto id_loop;
Imaginary_n:        if ((lexchr = *++p) == 'n') goto Imaginary_a2;      goto id_loop;
Imaginary_a2:       if ((lexchr = *++p) == 'a') goto Imaginary_r;       goto id_loop;
Imaginary_r:        if ((lexchr = *++p) == 'r') goto Imaginary_y;       goto id_loop;
Imaginary_y:        if ((lexchr = *++p) == 'y') goto Imaginary_sink;    goto id_loop;
Imaginary_sink:     switch (lexchr = *++p)
                    {
                        case '0' ... '9':
                        case 'A' ... 'Z':
                        case '_':
                        case 'a' ... 'z': goto id_advance;
                        default: { return Token(TokenType::KW_IMAGINARY_, loc); }
                    }
        }
    }
}
