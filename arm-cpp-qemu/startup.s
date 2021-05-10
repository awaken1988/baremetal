.global _reset_entry

_reset_entry:
    nop
    nop
    nop
    b _mainCRTStartup

_stack_init:
    blx lr
