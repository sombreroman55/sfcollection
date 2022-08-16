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
  SFAS::SFAS(std::string filename, std::string src) : _src_filename(filename), _src_buffer(src)
  {
    _symbol_table = {};
  }

  SFAS::~SFAS() = default;

  void SFAS::_tokenize(void)
  {
    _token_stream = _lexer.tokenize_buffer(_src_buffer);
  }

  void SFAS::_pass_zero(void)
  {
    // TODO
  }

  void SFAS::_pass_one(void)
  {
    // Parse tokens into instructions based on operand forms
  }

  std::vector<uint8_t> SFAS::_pass_two(void)
  {
    std::vector<uint8_t> v;
    return v;
  }

  void SFAS::_write_object_file(std::vector<uint8_t> instructions)
  {
    std::string object_filename = _src_filename + ".o";
  }

  void SFAS::assemble(void)
  {
    _tokenize();  // tokenize file, populate token vector
#ifndef NDEBUG
    std::cout << "Source buffer for file " << _src_filename << ":" << std::endl;
    std::cout << _src_buffer << "\n" << std::endl;
    std::cout << "Token stream for file " << _src_filename << ":" << std::endl;
    for (auto token : _token_stream)
    {
      std::cout << token.to_string() << std::endl;
    }
#endif

    /* TODO */
    // _pass_zero();                      // TODO: traverse token vector and execute directives
    // _pass_one();                       // traverse updated token vector and populate symbol table
    // auto instructions = _pass_two();   // traverse token vector and assemble object file
    // _write_object_file(instructions);  // write object file to disk
  }
}
