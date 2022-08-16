/* instruction.hh
 *
 *
 *
 *
 */

#pragma once

#include <string>
#include <cstdint>

namespace sfas
{
  enum class AdressingMode
  {

  };
  struct Instruction
  {
    public:
      Instruction();
      ~Instruction();
    private:
      uint8_t     opcode;
      std::string name;
      int         size;
  };
}
