/* token.hh
 *
 * Token data type definition
 *
 */

#pragma once

#include <cstdint>
#include <string>

namespace sfas
{
  enum class TokenType : uint16_t
  {
    NONE = 0,

    // Register keywords
    REG_A,
    REG_B,
    REG_C,
    REG_DBR,
    REG_DP,
    REG_D,
    REG_P,
    REG_PBR,
    REG_PC,
    REG_S,
    REG_X,
    REG_Y,

    // Instruction keywords
    INS_ADC,
    INS_AND,
    INS_ASL,
    INS_BCC,
    INS_BCS,
    INS_BEQ,
    INS_BIT,
    INS_BMI,
    INS_BNE,
    INS_BPL,
    INS_BRA,
    INS_BRK,
    INS_BRL,
    INS_BVC,
    INS_BVS,
    INS_CLC,
    INS_CLD,
    INS_CLI,
    INS_CLV,
    INS_CMP,
    INS_COP,
    INS_CPX,
    INS_CPY,
    INS_DEC,
    INS_DEX,
    INS_DEY,
    INS_EOR,
    INS_INC,
    INS_INX,
    INS_INY,
    INS_JMP,
    INS_JML,
    INS_JSR,
    INS_JSL,
    INS_LDA,
    INS_LDX,
    INS_LDY,
    INS_LSR,
    INS_MVN,
    INS_MVP,
    INS_NOP,
    INS_ORA,
    INS_PEA,
    INS_PER,
    INS_PHA,
    INS_PHB,
    INS_PHD,
    INS_PHK,
    INS_PHP,
    INS_PHX,
    INS_PHY,
    INS_PLA,
    INS_PLB,
    INS_PLD,
    INS_PLP,
    INS_PLX,
    INS_PLY,
    INS_REP,
    INS_ROL,
    INS_ROR,
    INS_RTI,
    INS_RTL,
    INS_RTS,
    INS_SBC,
    INS_SEC,
    INS_SED,
    INS_SEI,
    INS_SEP,
    INS_STA,
    INS_STP,
    INS_STX,
    INS_STY,
    INS_STZ,
    INS_TAX,
    INS_TAY,
    INS_TCD,
    INS_TCS,
    INS_TDC,
    INS_TRB,
    INS_TSB,
    INS_TSC,
    INS_TSX,
    INS_TXA,
    INS_TXS,
    INS_TXY,
    INS_TYA,
    INS_TYX,
    INS_WAI,
    INS_WDM,
    INS_XBA,
    INS_XCE,

    // Directive keywords
    // TODO

    // Non-keyword tokens
    IDENTIFIER,
    DECIMAL,
    HEX,
    BINARY,
    ADDRESS,
    LSQUARE,
    RSQUARE,
    LPAREN,
    RPAREN,
    COMMA,
    DOT,
    COLON,
    COMMENT,

    ERROR,
    NEWLINE,
    END,

    NUMTYPES
  };

  const std::string tokenTypeStrs[(int)TokenType::NUMTYPES] =
  {
    "NONE",

    // Register keywords
    "REG_A",
    "REG_B",
    "REG_C",
    "REG_DBR",
    "REG_DP",
    "REG_D",
    "REG_P",
    "REG_PBR",
    "REG_PC",
    "REG_S",
    "REG_X",
    "REG_Y",

    // Instruction keywords
    "INS_ADC",
    "INS_AND",
    "INS_ASL",
    "INS_BCC",
    "INS_BCS",
    "INS_BEQ",
    "INS_BIT",
    "INS_BMI",
    "INS_BNE",
    "INS_BPL",
    "INS_BRA",
    "INS_BRK",
    "INS_BRL",
    "INS_BVC",
    "INS_BVS",
    "INS_CLC",
    "INS_CLD",
    "INS_CLI",
    "INS_CLV",
    "INS_CMP",
    "INS_COP",
    "INS_CPX",
    "INS_CPY",
    "INS_DEC",
    "INS_DEX",
    "INS_DEY",
    "INS_EOR",
    "INS_INC",
    "INS_INX",
    "INS_INY",
    "INS_JMP",
    "INS_JML",
    "INS_JSR",
    "INS_JSL",
    "INS_LDA",
    "INS_LDX",
    "INS_LDY",
    "INS_LSR",
    "INS_MVN",
    "INS_MVP",
    "INS_NOP",
    "INS_ORA",
    "INS_PEA",
    "INS_PER",
    "INS_PHA",
    "INS_PHB",
    "INS_PHD",
    "INS_PHK",
    "INS_PHP",
    "INS_PHX",
    "INS_PHY",
    "INS_PLA",
    "INS_PLB",
    "INS_PLD",
    "INS_PLP",
    "INS_PLX",
    "INS_PLY",
    "INS_REP",
    "INS_ROL",
    "INS_ROR",
    "INS_RTI",
    "INS_RTL",
    "INS_RTS",
    "INS_SBC",
    "INS_SEC",
    "INS_SED",
    "INS_SEI",
    "INS_SEP",
    "INS_STA",
    "INS_STP",
    "INS_STX",
    "INS_STY",
    "INS_STZ",
    "INS_TAX",
    "INS_TAY",
    "INS_TCD",
    "INS_TCS",
    "INS_TDC",
    "INS_TRB",
    "INS_TSB",
    "INS_TSC",
    "INS_TSX",
    "INS_TXA",
    "INS_TXS",
    "INS_TXY",
    "INS_TYA",
    "INS_TYX",
    "INS_WAI",
    "INS_WDM",
    "INS_XBA",
    "INS_XCE",

    // Directive keywords
    // TODO

    // Non-keyword tokens
    "IDENTIFIER",
    "DECIMAL",
    "HEX",
    "BINARY",
    "ADDRES",
    "LSQUARE",
    "RSQUARE",
    "LPAREN",
    "RPAREN",
    "COMMA",
    "DOT",
    "COLON",
    "COMMENT",

    "ERROR",
    "NEWLINE",
    "END"
  };

  class Token
  {
    public:
      std::string to_string(void);
      std::string get_lexeme(void);
      Token();
      Token(TokenType type, std::string lexeme);
      Token(TokenType type, std::string lexeme, uint16_t value);
      ~Token();

    private:
      TokenType   type_;
      std::string lexeme_;
      uint16_t    value_;
      friend class Lexer;
  };
}
