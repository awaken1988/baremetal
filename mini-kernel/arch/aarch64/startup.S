.global .text.irqtable
.global _reset_entry


//--------------------------------
// exception vector table
//	see infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.den0024a/CHDHCCGJ.html
//--------------------------------
.section .text.irqtable
exception_table_start:

	.macro add_exception addr, name, callname
		.org     \addr
		\name:
		b \callname
	.endm

	.macro add_weak_handler name
		.weak \name
		\name:
		nop
		b \name
	.endm

	//vector table
	#define EXCEPTION_ENTRY(X_ADDR, X_NAME) add_exception X_ADDR X_NAME X_NAME##__handler
		#include "vector_tbl.h"
	#undef EXCEPTION_ENTRY

	//weak handlers
	#define EXCEPTION_ENTRY(X_ADDR, X_NAME) add_weak_handler X_NAME##__handler
		#include "vector_tbl.h"
	#undef EXCEPTION_ENTRY

_reset_entry:

    //set vector table
    ldr x0, =exception_table_start
    msr VBAR_EL1, x0
    nop

    //do not generate an exception on simd fp
    mov x1, #(0x3 << 20)
    msr cpacr_el1, x1
    isb
    nop
    
    b _mainCRTStartup
