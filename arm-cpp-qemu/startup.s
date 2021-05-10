@ references:
@   https://www.bravegnu.org/gnu-eprog/c-startup.htmls

.global _reset_entry

.section .text.vectbl
    b reset_handler      /* 0x0  Reset Handler */  
    b .                  /* 0x4  Undefined Instruction */
    b .                  /* 0x8  Software Interrupt */
    b .                  /* 0xC  Prefetch Abort */
    b .                  /* 0x10 Data Abort */
    b .                  /* 0x14 Reserved */
    b .                  /* 0x18 IRQ */   

_reset_entry:
reset_handler:
    @stack
        ldr sp, =__stack

    @clear bss
    ldr r0, =__bss_start__
    ldr r1, =__bss_end__
    mov r2, #0
    clear_bss_start:
        cmp r0, r1
        bhs clear_bss_end
        str r2, [r0], #4
    clear_bss_end:

    @ .init and .fini sections
	ldr	r0, =__libc_fini_array
	bl	atexit
	bl	__libc_init_array
    
    b main


