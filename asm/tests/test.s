GetAngle:   REP #$20
    LDY #$00
    LDA $02
    SEC
    SBC $06
    BPL If_Plus20
    INY
    EOR.w #$FFFF
    INC A
If_Plus20:    STA $02
    LDA $00
    SEC
    SBC $04
    BPL If_Plus21
    INY
    INY
    EOR.w #$FFFF
    INC A
If_Plus21:    STA $00
    STY $04
    BEQ X_Zero
    CMP.w #$0100
    XBA
    ROR A
    XBA
    TAY
    LDA $02
    BEQ Y_Zero
    CMP.w #$0100
    XBA
    ROR A
    AND.w #$FF80
    STA $4204
    STY $4206
    LDA $4214
    LSR A
    LSR A
    LSR A
    LSR A
    CMP.w #$0100
    SEP #$20
    BCC NoOverFlow
    LDA #$FF
NoOverFlow:   TAY
    LDA AtanTable,y
    LSR $04
    BCS If_Plus30
    EOR #$FF        ;\
    INC A           ; | θ:360°-θ
    BEQ If_Plus30   ; |
    INC $01         ;/
If_Plus30:    LSR $04
    BCS If_Plus31
    EOR #$FF        ;\
    INC A           ; | θ:180°-θ
    BNE If_Plus31   ; |
    INC $01         ;/
If_Plus31:    STA $00
    LDA #$FE
    TRB $01
    RTS

X_Zero:     SEP #$20
    LDY #$00
    LSR $04
    BCS If_Plus32
    INY
If_Plus32:    STY $01
    LDA #$80
    STA $00
    LDY #$FF
    RTS

Y_Zero:     SEP #$20
    STZ $00
    LDY #$00
    LDA $04
    AND #$02
    BNE If_Plus33
    INY
If_Plus33:    STY $01
    LDY #$00
    RTS

AtanTable:
db $00,$05,$0A,$0F,$13,$18,$1D,$21,$25,$29,$2D,$31,$34,$37,$3A,$3D
db $40,$42,$44,$46,$49,$4A,$4C,$4E,$50,$51,$53,$54,$55,$56,$58,$59
db $5A,$5B,$5C,$5D,$5D,$5E,$5F,$60,$60,$61,$62,$62,$63,$64,$64,$65
db $65,$66,$66,$67,$67,$68,$68,$68,$69,$69,$6A,$6A,$6A,$6B,$6B,$6B
db $6C,$6C,$6C,$6C,$6D,$6D,$6D,$6D,$6E,$6E,$6E,$6E,$6F,$6F,$6F,$6F
db $6F,$70,$70,$70,$70,$70,$71,$71,$71,$71,$71,$71,$71,$72,$72,$72
db $72,$72,$72,$72,$73,$73,$73,$73,$73,$73,$73,$73,$74,$74,$74,$74
db $74,$74,$74,$74,$74,$74,$75,$75,$75,$75,$75,$75,$75,$75,$75,$75
db $75,$75,$76,$76,$76,$76,$76,$76,$76,$76,$76,$76,$76,$76,$76,$76
db $76,$77,$77,$77,$77,$77,$77,$77,$77,$77,$77,$77,$77,$77,$77,$77
db $77,$77,$77,$78,$78,$78,$78,$78,$78,$78,$78,$78,$78,$78,$78,$78
db $78,$78,$78,$78,$78,$78,$78,$78,$78,$78,$79,$79,$79,$79,$79,$79
db $79,$79,$79,$79,$79,$79,$79,$79,$79,$79,$79,$79,$79,$79,$79,$79
db $79,$79,$79,$79,$79,$79,$79,$79,$79,$7A,$7A,$7A,$7A,$7A,$7A,$7A
db $7A,$7A,$7A,$7A,$7A,$7A,$7A,$7A,$7A,$7A,$7A,$7A,$7A,$7A,$7A,$7A
db $7A,$7A,$7A,$7A,$7A,$7A,$7A,$7A,$7A,$7A,$7A,$7A,$7A,$7A,$7A,$80
