/* pptoken.cc
 *
 * Preprocessor token class
 *
 */

#include "pptoken.hh"

namespace SFCC
{
    namespace DataStructures
    {
        PPToken::PPToken(std::string _lexeme, PPTokenType _type) : lexeme(_lexeme), type(_type) {}
        PPToken::~PPToken() {}
    }
}
