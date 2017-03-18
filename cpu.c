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
	volatile uint32_t typer = GICD_TYPER(base);
	uint32_t itl = 32 * ( (typer&0x1F) + 1  );		//extract irq lines

	k_print("GIC: IRQ lines=");
	k_print_ull(itl, PRINT_FLAG_HEX);
	k_print("\r\n");

	//disable distributor
	GICD_CTLR(base) = 0x0;	//enable forwarding irq

	//TODO: we must probe for avail interrupts
	//enable all interrupts
	for(int iReg=0; iReg<itl/32; iReg++) {
		GICD_ISENABLERn(base, iReg) = 0xFFFFFFFF;	//enable all interrupts
		GICD_IGROUPR(base, iReg) 	= 0xFFFFFFFF;	//all interrupts are group 1
	}

	//set the target processor for each irq
	//	we set all cpu!
	for(int iReg=0; iReg<itl/8; iReg++) {
		GICD_TARGETSR(base, iReg) = 0x01010101;
	}

	GICD_CTLR(base) = 0x1;	//enable forwarding irq
}

void gic_cpu_init(uptr_t base)
{
	GICC_PMR(base) = 0xFF;	//irq mask; accept all interrupts
	GICC_CTRL(base) = 		0x1<<0	//enable Grp 0
						|	0x1<<1;	//enable Grp 1
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






