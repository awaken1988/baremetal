.extern main



reset_entry:
	nop
	nop
	nop

	//setup stack
	ldr x30, =stack_top

	b main
