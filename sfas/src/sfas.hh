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

#include "lexer.hh"
#include "token.hh"

namespace sfas
{
  class SFAS
  {
    private:
      std::string                               _src_filename;
      std::string                               _src_buffer;
      std::unordered_map<std::string, uint16_t> _symbol_table;
      std::vector<Token>                        _token_stream;
      Lexer                                     _lexer;

      void                 _tokenize(void);
      void                 _pass_zero(void);
      void                 _pass_one(void);
      std::vector<uint8_t> _pass_two(void);
      void                 _write_object_file(std::vector<uint8_t>);
    public:
      SFAS(std::string filename, std::string src);
      ~SFAS();
      void assemble(void);
  };
}
