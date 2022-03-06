/* pptoken.cc
 *
 * Preprocessor token class
 *
 */

#include "token.hh"

namespace SFCC
{
    namespace DataStructures
    {
        PPToken::PPToken(std::string _lexeme, PPTokenType type) : lexeme(_lexeme), type(_type) {}
        ~PPToken::PPToken() {}
    }
}
