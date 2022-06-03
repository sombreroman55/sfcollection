/*
 *
 *
 *
 */

#include "parser.hh"
#include "instruction.hh"

namespace sfas
{
    Parser::Parser() {}
    Parser::~Parser() = default;
    Instruction Parser::parse(std::string line)
    {
        _lexer.get_next_token(
    }
}
