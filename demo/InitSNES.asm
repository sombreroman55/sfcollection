;-----------------------------------------------------------------------------
; Initialize SNES
;-----------------------------------------------------------------------------
.MACRO InitializeSNES
  sei         ; disable interrupts
  clc         ; set to native mode
  xce

  rep #$38    ; mem/A = 16bit, X/Y = 16bit
              ; decimal mode off
  ldx #$1FFF  ; Reset stack
  txs

  ; jump to start of init code
  jsl $008000
  sep #$20    ; mem/A = 8bit
.ENDM
;-----------------------------------------------------------------------------

;-----------------------------------------------------------------------------
.BANK 0 SLOT 0
.ORG HEADER_OFF
.SECTION "InitSNESCode" FORCE

InitSNES:
  phk           ; set Data Bank = Program Bank
  plb

  lda #$0000    ; set Direct Page = $0000
  tcd

  ldx $1FFD     ; load top of stack in to X
  stx $4372     ; store X in to $4372
  ldx $1FFD
  stx $4374

  sep #$20      ; mem/A = 8bit

  lda #$8F
  sta $2100     ; turn screen off for now

  ldx #$2101
_Loop00:
  stz $00,X
  inx
  cpx #210D
  bne _Loop00

_Loop01:
  stz $00,X
  inx
  cpx #2115
  bne _Loop1

  lda #$80
  sta $2115

  stz $2116
  stz $2117
