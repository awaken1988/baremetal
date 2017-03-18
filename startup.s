.extern main
.global reset_entry



//--------------------------------
// exception vector table
//	see infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.den0024a/CHDHCCGJ.html
//--------------------------------
.section .text.irqtable
exception_table_start:

	//current el with sp0
	.org 0x000
	exception_entry_currel_sp0_syn:
		b .
	.org 0x080
	exception_entry_currel_sp0_irq:
		b .
	.org 0x100
	exception_entry_currel_sp0_fiq:
		b .
	.org 0x180
	exception_entry_currel_sp0_serror:
		b .

	//current el with spx
	.org 0x200
	exception_entry_currel_spx_syn:
		b .
	.org 0x280
	exception_entry_currel_spx_irq:
		b .
	.org 0x300
	exception_entry_currel_spx_fiq:
		b .
	.org 0x380
	exception_entry_currel_spx_serror:
		b .

	//lower el with aarch64
	.org 0x400
	exception_entry_lowerel_aarch64_syn:
		b .
	.org 0x480
	exception_entry_lowerel_aarch64_irq:
		b .
	.org 0x500
	exception_entry_lowerel_aarch64_fiq:
		b .
	.org 0x580
	exception_entry_lowerel_aarch64_serror:
		b .

	//lower el with aarch32
	.org 0x600
	exception_entry_lowerel_aarch32_syn:
		b .
	.org 0x680
	exception_entry_lowerel_aarch32_irq:
		b .
	.org 0x700
	exception_entry_lowerel_aarch32_fiq:
		b .
	.org 0x780
	exception_entry_lowerel_aarch32_serror:
		b .




.section .text
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



	mrs x0, s3_1_c15_c3_0

	//--------------------
	//-exceptions
	//--------------------

	//set VBAR EL0
	ldr x0, =exception_table_start
	msr VBAR_EL1, x0

	//! will be moved to main
	//allow interrupts
	//mrs x0, DAIF
	//mov x1, xzr
	//orr x1, x1, #(1<<6)
	//orr x1, x1, #(1<<7)
	//orr x1, x1, #(1<<8)
	//mvn x1, x1
	//and x0, x0, x1
	//msr DAIF, x0
	//mrs x0, DAIF

	//--------------------
	//-system timer-------
	//--------------------
	//! will be moved to main

	//set system timer frequency
	//ldr x0, =1000000	//use 1MHZ
	//msr CNTFRQ_EL0, x0

	//set downcounter
	//ldr x0, =100000
	//msr CNTP_TVAL_EL0, x0	//set downcounter value
	//ldr x0, =0x1
	//msr CNTP_CTL_EL0, x0	//activate downcounter

	//loooop:
	//mrs x0, CNTP_CTL_EL0
	//b loooop

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
