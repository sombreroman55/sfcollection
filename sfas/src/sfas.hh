/*
 *
 *
 *
 */

#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "token.hh"

namespace sfas
{
    class SFAS
    {
    private:
        std::string                               _src_buffer;
        std::unordered_map<std::string, uint16_t> _symbol_table;
        std::vector<std::vector<Token>>           _token_stream;

        void                 _tokenize(void);
        void                 _pass_zero(void);
        void                 _pass_one(void);
        std::vector<uint8_t> _pass_two(void);
    public:
        SFAS(std::string src);
        ~SFAS();
        void assemble(void);
    };
}
