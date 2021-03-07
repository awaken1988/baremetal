.global _reset_entry

_reset_entry:
    nop
    nop
    nop
    mov x1, #(0x3 << 20)
    msr cpacr_el1, x1
    isb
    nop
    nop
    nop
    b _mainCRTStartup
