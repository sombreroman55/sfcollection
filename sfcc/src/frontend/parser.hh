/* parser.hh
 *
 * Parser class definition
 */

#ifndef PARSER_HH
#define PARSER_HH

#include <string>
#include "token.hh"

namespace SFCC
{
    namespace Frontend
    {
        class Parser
        {
            public:
                Parser() {}
                SFCC::DataStrucures::Token getNextToken(char* p);
            private:
                std::string _buffer;
        };
    }
}

#endif // PARSER_HH
