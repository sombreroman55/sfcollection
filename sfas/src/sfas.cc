/*
 *
 *
 *
 *
 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "sfas.hh"

namespace sfas
{
    SFAS::SFAS(std::string src) : _src_buffer(src)
    {
        _symbol_table = {};
    }

    SFAS::~SFAS() = default;

    void SFAS::_tokenize(void)
    {
        std::stringstream _src_stream(_src_buffer);
        std::string line;
        int line_no = 1;
        while (std::getline(std::cin, line))
        {
            _parser::parse(line, line_no++);
        }
    }

    void _pass_zero(void)
    {
    }

    void _pass_one(void)
    {
    }

    std::vector<uint8_t> _pass_two(void)
    {
    }

    void SFAS::assemble(void)
    {
        std::cout << src << std::endl;
        _tokenize();   // tokenize file
        _pass_zero();  // execute directives
        _pass_one();   // populate symbol table
        _pass_two();   // assemble object file
    }
}
