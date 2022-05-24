/* token.hh
 *
 * Token class representation
 */

#ifndef TOKEN_HH
#define TOKEN_HH

#include <string>
#include <cstdint>

namespace SFCC
{
    namespace DataStructures
    {
        enum class TokenType : uint8_t
        {
            // Preprocessor tokens
            PP_NONTOKEN = 0,
            PP_HEADER_ANGLE,
            PP_HEADER_QUOTE,
            PP_NUMBER,
            PP_IF,
            PP_ELIF,
            PP_ELSE,
            PP_IFDEF,
            PP_IFNDEF,
            PP_ENDIF,
            PP_INCLUDE,
            PP_DEFINE,
            PP_DEFINED,
            PP_UNDEF,
            PP_LINE,
            PP_ERROR,
            PP_PRAGMA,

            // Keywords
            KW_AUTO,
            KW_BREAK,
            KW_CASE,
            KW_CHAR,
            KW_CONST,
            KW_CONTINUE,
            KW_DEFAULT,
            KW_DO,
            KW_DOUBLE,
            KW_ELSE,
            KW_ENUM,
            KW_EXTERN,
            KW_FLOAT,
            KW_FOR,
            KW_GOTO,
            KW_IF,
            KW_INLINE,
            KW_INT,
            KW_LONG,
            KW_REGISTER,
            KW_RESTRICT,
            KW_RETURN,
            KW_SHORT,
            KW_SIGNED,
            KW_SIZEOF,
            KW_STATIC,
            KW_STRUCT,
            KW_SWITCH,
            KW_TYPEDEF,
            KW_UNION,
            KW_UNSIGNED,
            KW_VOID,
            KW_VOLATILE,
            KW_WHILE,
            KW_BOOL_,
            KW_COMPLEX_,
            KW_IMAGINARY_,

            // Constants and identifiers
            IDENTIFIER,
            CONSTANT_INT,
            CONSTANT_FLOAT,
            CHAR_CONSTANT,
            STRING_LITERAL,

            // Punctuators
            PUNC_LSQUARE,
            PUNC_RSQUARE,
            PUNC_LPAREN,
            PUNC_RPAREN,
            PUNC_LCURLY,
            PUNC_RCURLY,
            PUNC_DOT,
            PUNC_ARROW,
            PUNC_PLUSPLUS,
            PUNC_MINUSMINUS,
            PUNC_AMP,
            PUNC_STAR,
            PUNC_PLUS,
            PUNC_MINUS,
            PUNC_TILDE,
            PUNC_BANG,
            PUNC_SLASH,
            PUNC_PERCENT,
            PUNC_LSHIFT,
            PUNC_RSHIFT,
            PUNC_LT,
            PUNC_GT,
            PUNC_LTE,
            PUNC_GTE,
            PUNC_EQ,
            PUNC_NEQ,
            PUNC_XOR,
            PUNC_BINOR,
            PUNC_LOGAND,
            PUNC_LOGOR,
            PUNC_QUESTION,
            PUNC_COLON,
            PUNC_SEMICOLON,
            PUNC_ELLIPSIS,
            PUNC_ASSIGN,
            PUNC_RMW_MULT,
            PUNC_RMW_DIV,
            PUNC_RMW_MOD,
            PUNC_RMW_ADD,
            PUNC_RMW_MINUS,
            PUNC_RMW_LSHIFT,
            PUNC_RMW_RSHIFT,
            PUNC_RMW_BINAND,
            PUNC_RMW_BINXOR,
            PUNC_RMW_BINOR,
            PUNC_COMMA,
            PUNC_POUND,
            PUNC_POUNDPOUND,

            // Internal tokens
            INTERNAL_EOF,
            INTERNAL_ERROR,

            NUM_TOKENS
        };

        struct Location
        {
            int line;
            int col;
        };

        class Token
        {
            public:
                Token(TokenType _type, Location _loc);
                Token(TokenType _type, Location _loc, std::string _lexeme);
                ~Token() = default;
#ifdef DEBUG
                std::string to_string(void);
#endif // DEBUG

            private:
                std::string lexeme;
                TokenType   type;
                Location    location;
        };
    }
}

#endif // TOKEN_HH
