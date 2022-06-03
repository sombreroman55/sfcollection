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
    struct Instruction
    {
    private:
        std::string name;
        uint8_t     opcode;
        int         size;
    };
}
