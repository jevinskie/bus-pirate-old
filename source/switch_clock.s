    .include "p24FJ64GA002.inc"
    .text
    .global _switch_clocks
_switch_clocks:
    ; FIXME: count number of cycles to disable interrupts for
    disi #36
    mov #OSCCONH, w1
    mov.b #0x02, w0
    mov.b #0x78, w2
    mov.b #0x9A, w3
    mov.b w2, [w1]
    mov.b w3, [w1]
    mov.b wreg, OSCCONH
    mov #OSCCONL, w1
    mov.b #0x01, w0
    mov.b #0x46, w2
    mov.b #0x57, w3
    mov.b w2, [w1]
    mov.b w3, [w1]
    mov.b wreg, OSCCONL
    return
