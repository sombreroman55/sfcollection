/*
 *
 *
 *
 */

#pragma once

#include "lexer.hh"

namespace sfas
{
    class Parser
    {
    private:
        Lexer _lexer;
    public:
        Parser();
        ~Parser();
        Instruction parse (std::string line);
    };
}
