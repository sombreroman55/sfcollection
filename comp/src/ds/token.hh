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
            none,
            keyword,
            identifier,
            constant,
            string_literal,
            punctuator
        };

        class Token
        {
            public:
                Token(std::string _lexeme, TokenType _type);
                ~Token();

            private:
                std::string lexeme;
                TokenType type;
        };
    }
}

#endif // TOKEN_HH
