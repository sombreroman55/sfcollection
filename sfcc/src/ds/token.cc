/* token.cc
 *
 * Token class
 *
 */

#include "token.hh"

namespace SFCC
{
    namespace DataStructures
    {
        Token::Token(TokenType _type, Location _loc)
            : type(_type)
            , location(_loc)

        {
        }

        Token::Token(TokenType _type, Location _loc, std::string _lexeme)
            : type(_type)
            , location(_loc)
            , lexeme(_lexeme)
        {
        }

        std::string Token::to_string(void)
        {
            return "test";
        }
    }
}
