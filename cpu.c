#include "cpu.h"
#include "kernel_lib.h"



void cpu_irq_set(bool_t enable, interrupt_flag_t irq)
{
  register uint32_t msr_val = 0;

  //get DAIF value
  asm volatile("mrs %[val], DAIF"
                  : [val] "=r" (msr_val)
                  :
                  : "memory");

  //change DAIF bits
  if( enable )
    msr_val &= ~irq;
  else
    msr_val |= irq;

  //write back
  asm volatile("msr DAIF, %[val]"
                  :
                  : [val] "r" (msr_val)
                  : );
}



void gic_distributor_init(uptr_t base)
{

}

void gic_cpu_init(uptr_t base)
{

}

//TODO: add clock rate
void cpu_timer_init()
{
	//set timer frequ to 1MHZ
	asm volatile("ldr x0, =1000000");
	asm volatile("msr CNTFRQ_EL0, x0");

	//set downcounter
	asm volatile("ldr x0, =100000");
	asm volatile("msr CNTP_TVAL_EL0, x0");	//set downcounter value
	asm volatile("ldr x0, =0x1");
	asm volatile("msr CNTP_CTL_EL0, x0");	//activate downcounter
}

//----------------------------------------------------------
//
// gic
//
//----------------------------------------------------------
#define GICC_CTLR		(0x000)
#define GICC_PMR		(0x004)
#define GICC_IAR		(0x00C)
#define GICC_EOIR		(0x010)

#define GICC_CTLR_ENABLEGRP0	(1 << 0)
#define GICC_CTLR_ENABLEGRP1	(1 << 1)
#define GICC_CTLR_FIQEN		(1 << 3)

#define GICD_CTLR		(0x000)
#define GICD_TYPER		(0x004)
#define GICD_IGROUPR(n)		(0x080 + (n) * 4)
#define GICD_ISENABLER(n)	(0x100 + (n) * 4)
#define GICD_ICENABLER(n)	(0x180 + (n) * 4)
#define GICD_ISPENDR(n)		(0x200 + (n) * 4)
#define GICD_ICPENDR(n)		(0x280 + (n) * 4)
#define GICD_IPRIORITYR(n)	(0x400 + (n) * 4)
#define GICD_ITARGETSR(n)	(0x800 + (n) * 4)
#define GICD_SGIR		(0xF00)

#define GICD_CTLR_ENABLEGRP0	(1 << 0)
#define GICD_CTLR_ENABLEGRP1	(1 << 1)

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

		if( 0 == iLine ) {
			UINT32_REF(dist_base+GICD_IGROUPR(iLine)) = 0xffff00ff;
		} else {
			UINT32_REF(dist_base+GICD_IGROUPR(iLine)) = 0xffffffff;
		}
	}

	UINT32_REF(dist_base+GICD_CTLR) = GICD_CTLR_ENABLEGRP0 | GICD_CTLR_ENABLEGRP1;

	//int cpu
	UINT32_REF(cpu_base+GICD_IGROUPR(0) ) 	= 0xffff00ff;
	UINT32_REF(cpu_base+GICC_PMR) 			= 0x80;
	UINT32_REF(cpu_base+GICC_CTLR) 			= GICC_CTLR_ENABLEGRP0 | GICC_CTLR_ENABLEGRP1 | GICC_CTLR_FIQEN;
}

void gic_set_pending(uptr_t dist_base)
{
	UINT32_REF(dist_base+GICD_SGIR) = 0x3 | 0x1<<16;
}




