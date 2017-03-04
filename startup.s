.extern main
.global reset_entry



//--------------------------------
// exception vector table
//	see infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.den0024a/CHDHCCGJ.html
//--------------------------------
exception_table_start:
	//Current EL with SP0 (we don't handle this)
	.org 0x000
		b not_handled_exception
	.org 0x080
		b not_handled_exception
	.org 0x100
		b not_handled_exception
	.org 0x180
			b not_handled_exception
	//Current EL with SPx (we don't handle this)
	.org 0x200
		b c_exception_el1h_syn
	.org 0x280
		b el1_spx_irq
	.org 0x300
			b el1_spx_fiq
	.org 0x380
			b el1_spx_serror

	//the other exceptions are ignored
	.rept 256
	b .
	.endr


//--------------------------------
// exception handler
//--------------------------------
not_handled_exception:
	b .

el1_spx_syn:
	nop
	nop
	nop
	b .

el1_spx_irq:
	nop
	nop
	nop
	b .

el1_spx_fiq:
	nop
	nop
	nop
	b .

el1_spx_serror:
	nop
	nop
	nop
	b .


//--------------------------------
// prepare the cpu for c
//--------------------------------
reset_entry:

	//--------------------
	//-exceptions
	//--------------------

	//set VBAR EL0
	ldr x0, =exception_table_start
	msr VBAR_EL1, x0

	//allow interrupts
	mrs x0, DAIF
	msr DAIF, xzr
	mrs x0, DAIF

	//--------------------
	//-system timer-------
	//--------------------

	//set system timer frequency
	ldr x0, =1000000	//use 1MHZ
	msr CNTFRQ_EL0, x0

	svc #0
	//set downcounter
	ldr x0, =100000
	msr CNTP_TVAL_EL0, x0	//set downcounter value
	ldr x0, =0x1
	msr CNTP_CTL_EL0, x0	//activate downcounter

	//loooop:
	//	mrs x0, CNTP_CTL_EL0
	//	b loooop

	//timer_el0:
	//	mrs x0, CNTPCT_EL0

	//--------------------
	//-prepare cpu for c
	//--------------------
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
