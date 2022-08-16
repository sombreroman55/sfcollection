/* lexer.hh
 *
 * Lexer class
 *
 */

#pragma once

#include <string>
#include <vector>
#include "token.hh"

namespace sfas
{
  class Lexer
  {
    private:
      enum class LexerState
      {
        token_start = 0,
        invalid,

        // instruction states
        instruction_a,
        instruction_ad,
        instruction_adc,
        instruction_an,
        instruction_and,
        instruction_as,
        instruction_asl,

        instruction_b,
        instruction_bc,
        instruction_bcc,
        instruction_bcs,
        instruction_be,
        instruction_beq,
        instruction_bi,
        instruction_bit,
        instruction_bm,
        instruction_bmi,
        instruction_bn,
        instruction_bne,
        instruction_bp,
        instruction_bpl,
        instruction_br,
        instruction_bra,
        instruction_brk,
        instruction_brl,
        instruction_bv,
        instruction_bvc,
        instruction_bvs,

        instruction_c,
        instruction_cl,
        instruction_clc,
        instruction_cld,
        instruction_cli,
        instruction_clv,
        instruction_cm,
        instruction_cmp,
        instruction_co,
        instruction_cop,
        instruction_cp,
        instruction_cpx,
        instruction_cpy,

        instruction_d,
        instruction_de,
        instruction_dec,
        instruction_dex,
        instruction_dey,

        instruction_e,
        instruction_eo,
        instruction_eor,

        instruction_i,
        instruction_in,
        instruction_inc,
        instruction_inx,
        instruction_iny,

        instruction_j,
        instruction_jm,

        instruction_l,

        instruction_m,

        instruction_n,
        instruction_no,
        instruction_nop,

        instruction_o,
        instruction_or,
        instruction_ora,

        instruction_p,

        instruction_r,
        instruction_re,
        instruction_rep,
        instruction_ro,
        instruction_rol,
        instruction_ror,
        instruction_rt,
        instruction_rti,
        instruction_rtl,
        instruction_rts,

        instruction_s,
        instruction_sb,
        instruction_sbc,
        instruction_se,
        instruction_sec,
        instruction_sed,
        instruction_sei,
        instruction_sep,
        instruction_st,
        instruction_sta,
        instruction_stp,
        instruction_stx,
        instruction_sty,
        instruction_stz,

        instruction_t,
        instruction_ta,
        instruction_tax,
        instruction_tay,
        instruction_tc,
        instruction_tcd,
        instruction_tcs,
        instruction_td,
        instruction_tdc,
        instruction_tr,
        instruction_trb,
        instruction_ts,
        instruction_tsb,
        instruction_tsc,
        instruction_tsx,
        instruction_tx,
        instruction_txa,
        instruction_txs,
        instruction_txy,
        instruction_ty,
        instruction_tya,
        instruction_tyx,

        instruction_w,
        instruction_wa,
        instruction_wai,
        instruction_wd,
        instruction_wdm,

        instruction_x,
        instruction_xb,
        instruction_xba,
        instruction_xc,
        instruction_xce,

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

      Token last_token;
    public:
      Lexer();
      ~Lexer();
      std::vector<Token> tokenize_buffer(std::string buffer);
  };
}
