/* lexer.hh
 *
 * Lexer interface
 */

#ifndef LEXER_HH
#define LEXER_HH

#include <string>
#include <fstream>
#include "token.hh"

namespace SFCC
{
    namespace Frontend
    {
        class Lexer
        {
            public:
                Lexer(std::ifstream file) {}
                SFCC::DataStructures::Token getNextToken(char* p);
            private:
                std::string _buffer;
        };
    }
}

#endif // LEXER_HH
