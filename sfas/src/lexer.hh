/* lexer.hh
 *
 * Lexer class
 *
 */

#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "token.hh"

namespace sfas
{
  class Lexer
  {
    private:
      const std::unordered_map<std::string, TokenType> keywords =
      {
        { "adc", TokenType::INS_ADC },
        { "and", TokenType::INS_AND },
        { "asl", TokenType::INS_ASL },
        { "bcc", TokenType::INS_BCC },
        { "bcs", TokenType::INS_BCS },
        { "beq", TokenType::INS_BEQ },
        { "bit", TokenType::INS_BIT },
        { "bmi", TokenType::INS_BMI },
        { "bne", TokenType::INS_BNE },
        { "bpl", TokenType::INS_BPL },
        { "bra", TokenType::INS_BRA },
        { "brk", TokenType::INS_BRK },
        { "brl", TokenType::INS_BRL },
        { "bvc", TokenType::INS_BVC },
        { "bvs", TokenType::INS_BVS },
        { "clc", TokenType::INS_CLC },
        { "cld", TokenType::INS_CLD },
        { "cli", TokenType::INS_CLI },
        { "clv", TokenType::INS_CLV },
        { "cmp", TokenType::INS_CMP },
        { "cop", TokenType::INS_COP },
        { "cpx", TokenType::INS_CPX },
        { "cpy", TokenType::INS_CPY },
        { "dec", TokenType::INS_DEC },
        { "dex", TokenType::INS_DEX },
        { "dey", TokenType::INS_DEY },
        { "eor", TokenType::INS_EOR },
        { "inc", TokenType::INS_INC },
        { "inx", TokenType::INS_INX },
        { "iny", TokenType::INS_INY },
        { "jmp", TokenType::INS_JMP },
        { "jml", TokenType::INS_JML },
        { "jsr", TokenType::INS_JSR },
        { "jsl", TokenType::INS_JSL },
        { "lda", TokenType::INS_LDA },
        { "ldx", TokenType::INS_LDX },
        { "ldy", TokenType::INS_LDY },
        { "lsr", TokenType::INS_LSR },
        { "mvn", TokenType::INS_MVN },
        { "mvp", TokenType::INS_MVP },
        { "nop", TokenType::INS_NOP },
        { "ora", TokenType::INS_ORA },
        { "pea", TokenType::INS_PEA },
        { "per", TokenType::INS_PER },
        { "pha", TokenType::INS_PHA },
        { "phb", TokenType::INS_PHB },
        { "phd", TokenType::INS_PHD },
        { "phk", TokenType::INS_PHK },
        { "php", TokenType::INS_PHP },
        { "phx", TokenType::INS_PHX },
        { "phy", TokenType::INS_PHY },
        { "pla", TokenType::INS_PLA },
        { "plb", TokenType::INS_PLB },
        { "pld", TokenType::INS_PLD },
        { "plp", TokenType::INS_PLP },
        { "plx", TokenType::INS_PLX },
        { "ply", TokenType::INS_PLY },
        { "rep", TokenType::INS_REP },
        { "rol", TokenType::INS_ROL },
        { "ror", TokenType::INS_ROR },
        { "rti", TokenType::INS_RTI },
        { "rtl", TokenType::INS_RTL },
        { "rts", TokenType::INS_RTS },
        { "sbc", TokenType::INS_SBC },
        { "sec", TokenType::INS_SEC },
        { "sed", TokenType::INS_SED },
        { "sei", TokenType::INS_SEI },
        { "sep", TokenType::INS_SEP },
        { "sta", TokenType::INS_STA },
        { "stp", TokenType::INS_STP },
        { "stx", TokenType::INS_STX },
        { "sty", TokenType::INS_STY },
        { "stz", TokenType::INS_STZ },
        { "tax", TokenType::INS_TAX },
        { "tay", TokenType::INS_TAY },
        { "tcd", TokenType::INS_TCD },
        { "tcs", TokenType::INS_TCS },
        { "tdc", TokenType::INS_TDC },
        { "trb", TokenType::INS_TRB },
        { "tsc", TokenType::INS_TSC },
        { "tsx", TokenType::INS_TSX },
        { "txa", TokenType::INS_TXA },
        { "txs", TokenType::INS_TXS },
        { "txy", TokenType::INS_TXY },
        { "tya", TokenType::INS_TYA },
        { "tyx", TokenType::INS_TYX },
        { "wai", TokenType::INS_WAI },
        { "wdm", TokenType::INS_WDM },
        { "xba", TokenType::INS_XBA },
        { "xce", TokenType::INS_XCE },
      };

      enum class LexerState
      {
        token_start = 0,
        invalid,

        regist,
        address,
        address_long,
        number_literal,
        decimal_number,
        hex_number,
        binary_number,
        directive,

        identifier,
        comment,

        num_lexer_states
      };

      // May need?
      // Token              last_token;

      // Utility functions
      // Adds token to token vector, lexeme is built from anchor and curront_pos
      void add_token(TokenType tt);
      bool is_identifier(char c, bool start);

      std::string        buffer;
      std::vector<Token> tokens;
      LexerState         state;
      int                anchor;
      int                current_pos;
    public:
      Lexer(std::string buffer);
      ~Lexer();
      std::vector<Token> tokenize();
  };
}
