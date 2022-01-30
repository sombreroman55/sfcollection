;------------------------------ Header File ---------------------------------
;   This is basically a combo of MarctheMER's and Neviksti's header files
; Perhaps reading their's will also help your understanding of the header,
; but I believe this will be the simplest method of defining your header,
; as Marc's doesn't provide a full explanation, and Neviksti's can be
; a bit more difficult for beginners (using the WLA directives is easier).
;----------------------------------------------------------------------------

;==LoRom==
.MEMORYMAP                      ; Begin describing the system architecture.
  SLOTSIZE $8000                ; The slot is $8000 bytes in size.
  DEFAULTSLOT 0                 ; There's only 1 slot in SNES.
  SLOT 0 $8000                  ; Define Slot 0's starting address
.ENDME                          ; End MemoryMap definition

.ROMBANKSIZE $8000              ; Every ROM bank is 32 KB in size
.ROMBANKS 8                     ; 2 Mbits - Tell WLA we want to use 8 ROM banks

.SNESHEADER
  ID "SNES"                     ; 1-4 letter string, just leave as "SNES"

  NAME "SNES Demo            "  ; Program Title - can't be over 21 bytes,
  ;    "123456789012345678901"  ; use spaces for unused bytes in the name.

  SLOWROM
  LOROM

  CARTRIDGETYPE $00             ; $00 = ROM only, see WLA documentation for others
  ROMSIZE $08                   ; $08 = 2Mbits,   see WLA docs for more...
  SRAMSIZE $00                  ; No SRAM         see WLA docs for more...
  COUNTRY $01                   ; $00 = JP, $01 = USA
  LICENSEECODE $00              ; Just use $00
  VERSION $00                   ; $00 = 1.00, $01 = 1.01, etc.
.ENDSNES

.SNESNATIVEVECTOR               ; Define Native Mode interrupt vector table
  COP EmptyHandler
  BRK EmptyHandler
  ABORT EmptyHandler
  NMI VBlank
  IRQ EmptyHandler
.ENDNATIVEVECTOR

.SNESEMUVECTOR                  ; Define Emulation Mode interrupt vector table
  COP EmptyHandler
  BRK EmptyHandler
  ABORT EmptyHandler
  NMI VBlank
  IRQ EmptyHandler
.ENDEMUVECTOR

.BANK 0 SLOT 0                  ; Defines the ROM bank and slot it is inserted into in memory.
.ORG 0                          ; .ORG 0 is reallly $8000, because the slot starts at $8000
.SECTION "EmptyVectors" SEMIFREE

EmtpyHandler
  rti
.ENDS

.EMPTYFILL $00
;---------------------------------- END -------------------------------------

