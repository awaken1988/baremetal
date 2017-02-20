.extern main
.global reset_entry


reset_entry:

	//setup stack
	ldr x0, =stack_top
	mov SP, x0

	//clear .bss
	ldr x0, =_bss_start
	ldr x1, =_bss_end
	bss_clear_loop:
		str xzr, [x0], #8
		cmp x0, x1
		bne bss_clear_loop

	b main
