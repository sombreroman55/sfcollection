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
        Token::Token(std::string _lexeme, TokenType type) : lexeme(_lexeme), type(_type) {}
        ~Token::Token() {}
    }
}
