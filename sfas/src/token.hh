/* token.hh
 *
 * Token data type definition
 *
 */

#include <cstdint>
#include <string>

#include "location.hh"

namespace sfas
{
    struct Token
    {
        typedef enum : uint16_t
        {
            TT_NONE = 0,

            // Register keywords
            TT_A,
            TT_B,
            TT_C,
            TT_DBR,
            TT_DP,
            TT_D,
            TT_P,
            TT_PBR,
            TT_PC,
            TT_S,
            TT_X,
            TT_Y,

            // Instruction keywords
            TT_ADC,
            TT_AND,
            TT_ASL,
            TT_BCC,
            TT_BCS,
            TT_BEQ,
            TT_BIT,
            TT_BMI,
            TT_BNE,
            TT_BPL,
            TT_BRA,
            TT_BRK,
            TT_BRL,
            TT_BVC,
            TT_BVS,
            TT_CLC,
            TT_CLD,
            TT_CLI,
            TT_CLV,
            TT_CMP,
            TT_COP,
            TT_CPX,
            TT_CPY,
            TT_DEC,
            TT_DEX,
            TT_DEY,
            TT_EOR,
            TT_INC,
            TT_INX,
            TT_INY,
            TT_JMP,
            TT_JSR,
            TT_LDA,
            TT_LDX,
            TT_LDY,
            TT_LSR,
            TT_MVN,
            TT_MVP,
            TT_NOP,
            TT_ORA,
            TT_PEA,
            TT_PER,
            TT_PHA,
            TT_PHB,
            TT_PHD,
            TT_PHK,
            TT_PHP,
            TT_PHX,
            TT_PHY,
            TT_PLA,
            TT_PLB,
            TT_PLD,
            TT_PLP,
            TT_PLX,
            TT_PLY,
            TT_REP,
            TT_ROL,
            TT_ROR,
            TT_RTI,
            TT_RTL,
            TT_RTS,
            TT_SBC,
            TT_SEC,
            TT_SED,
            TT_SEI,
            TT_SEP,
            TT_STA,
            TT_STP,
            TT_STX,
            TT_STY,
            TT_STZ,
            TT_TAX,
            TT_TAY,
            TT_TCD,
            TT_TCS,
            TT_TDC,
            TT_TRB,
            TT_TSB,
            TT_TSC,
            TT_TSX,
            TT_TXA,
            TT_TXS,
            TT_TXY,
            TT_TYA,
            TT_TYX,
            TT_WAI,
            TT_WDM,
            TT_XBA,
            TT_XCE,

            // Directive keywords
            // TODO

            // Non-keyword tokens
            TT_IDENTIFIER,
            TT_LSQUARE,
            TT_RSQUARE,
            TT_LPAREN,
            TT_RPAREN,
            TT_HASH,
            TT_DOLLAR,
            TT_PERCENT,
            TT_CARAT,
            TT_COMMA,
            TT_DOT,
            TT_COLON,
            TT_SEMICOLON,

            TT_NUMTYPES
        } TokenType;

        Token(TokenType type, std::string lexeme, Location loc);
        ~Token() = default;

        private:
        TokenType type_;
        std::string lexeme_;
        Location location_;
    };
}
