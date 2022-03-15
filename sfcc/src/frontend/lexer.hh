/* lexer.hh
 *
 * Lexer interface
 */

#ifndef LEXER_HH
#define LEXER_HH

#include <string>
#include <fstream>
#include <vector>
#include "token.hh"

namespace SFCC
{
    namespace Frontend
    {
        class Lexer
        {
            public:
                Lexer(std::string filename, std::string buffer);
                ~Lexer() = default;
                std::vector<SFCC::DataStructures::Token> lex(void);
            private:
                std::string _filename;
                std::string _buffer;
                SFCC::DataStructures::Token _getNextToken(const char* p);
        };
    }
}

#endif // LEXER_HH
