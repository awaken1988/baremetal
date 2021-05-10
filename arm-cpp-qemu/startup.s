.global _reset_entry

vectortable:
    b _reset_entry       /* 0x0  Reset Handler */  
    b .                  /* 0x4  Undefined Instruction */
    b .                  /* 0x8  Software Interrupt */
    b .                  /* 0xC  Prefetch Abort */
    b .                  /* 0x10 Data Abort */
    b .                  /* 0x14 Reserved */
    b .                  /* 0x18 IRQ */   

_reset_entry:

    @set VBAR
    ldr r0, =vectortable
    mcr	p15, 0, r0, c12, c0, 0	@Set VBAR
    
    b _mainCRTStartup

@stack init (called from _mainCRTStartup)
    .thumb
    .global _stack_init
    _stack_init:
        blx lr
