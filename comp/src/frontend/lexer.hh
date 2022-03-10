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
                Lexer(std::string filename);
                ~Lexer();
                std::vector<SFCC::DataStructures::Token> lex(void);
            private:
                SFCC::DataStructures::Token _getNextToken(char* p);
                std::ifstream _file;
                std::string _buffer;
        };
    }
}

#endif // LEXER_HH
