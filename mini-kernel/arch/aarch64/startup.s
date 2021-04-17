.global _reset_entry
.global exception_table_start

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

.org 0x800
_reset_entry:
    mov x1, #(0x3 << 20)
    msr cpacr_el1, x1
    isb

	ldr x0, =exception_table_start
	msr VBAR_EL1, x0	

    b _mainCRTStartup
