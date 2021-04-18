#include "gic.h"

void gic_init(uptr_t dist_base, uptr_t cpu_base)
{
	//init distributor
	uint32_t typer = UINT32_REF( dist_base + GICD_TYPER);
	uint32_t itl = 32 * ( (typer&0x1F) + 1  );		//extract irq lines

	//k_print("GIC: IRQ lines=");
	//k_print_ull(itl, PRINT_FLAG_HEX);
	//k_print("\r\n");

	/* Disable interrupts */
	for(size_t iLine=0; iLine<itl/32; iLine++) {

		UINT32_REF(dist_base+GICD_ICENABLER(iLine)) = 0xffffffff;
		UINT32_REF(dist_base+GICD_ICPENDR(iLine))	= 0xffffffff;	//set non pending

		UINT32_REF(dist_base+GICD_ISENABLER(iLine)) = 0xffffffff;
		

		if( 0 == iLine ) {
			UINT32_REF(dist_base+GICD_IGROUPR(iLine)) = 0xffff00ff;
		} else {
			UINT32_REF(dist_base+GICD_IGROUPR(iLine)) = 0xffffffff;
		}
	}

	UINT32_REF(dist_base+GICD_CTLR) = GICD_CTLR_ENABLEGRP0 | GICD_CTLR_ENABLEGRP1;

	//int cpu
	UINT32_REF(cpu_base+GICD_IGROUPR(0) ) 	= 0xffff00ff;
	UINT32_REF(cpu_base+GICC_PMR) 			= 0xFF;
	UINT32_REF(cpu_base+GICC_CTLR) 			= GICC_CTLR_ENABLEGRP0 | GICC_CTLR_ENABLEGRP1 | GICC_CTLR_FIQEN
												| 0x1<<2; //AckCtl
}

void gic_set_pending(uptr_t dist_base)
{
	UINT32_REF(dist_base+GICD_SGIR) = 0x3 | 0x1<<16;
}

iar_t gic_start_irq(uintptr_t cpu_base)
{
	iar_t ret;

	ret.val = *(UINT32_PTR(cpu_base + GICC_IAR));

	return ret;

}

void gic_end_irq(uintptr_t cpu_base, iar_t content)
{
	*UINT32_PTR(cpu_base + GICC_EOIR) = content.val;
}