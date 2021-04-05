#include "aarch64.h"
#include <cstddef>

using namespace std;


//TODO: remove these macros in future
#define UINT32_PTR(x) ((volatile uint32_t*)(x))
#define UINT64_PTR(x) ((volatile uint32_t*)(x))
#define UINT32_REF(x) ( *(UINT32_PTR(x)) )
#define UINT64_REF(x) ( *(UINT64_PTR(x)) )

void cpu_irq_set(bool enable, interrupt_flag_t irq)
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



void gic_distributor_init(uintptr_t base)
{

}

void gic_cpu_init(uintptr_t base)
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


void gic_init(uintptr_t dist_base, uintptr_t cpu_base)
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
	UINT32_REF(cpu_base+GICC_PMR) 			= 0xFF;
	UINT32_REF(cpu_base+GICC_CTLR) 			= GICC_CTLR_ENABLEGRP0 | GICC_CTLR_ENABLEGRP1 | GICC_CTLR_FIQEN
												| 0x1<<2; //AckCtl
}

void gic_set_pending(uintptr_t dist_base)
{
	UINT32_REF(dist_base+GICD_SGIR) = 0x3 | 0x1<<16;
}

void cpu_print_state()
{
	uint32_t curr_el = (mrs_current_el()>>2) & 0x3;

	//k_print("CPU: EL=%x01\n\r", (variant_t[]){
	//			VA_UNUM( curr_el )  });

}


uint32_t mrs_current_el()
{
	uint32_t currEL = 0x0;

	asm volatile("mrs %0, CurrentEL"
					:"=r"	(currEL)
					:
					:);

	return currEL;
}

//---------------------------
//interrupt handlers
//---------------------------

extern "C" void __attribute__((interrupt)) currel_spx_syn__handler(void) {
   int a = 0;
   a++;
}

