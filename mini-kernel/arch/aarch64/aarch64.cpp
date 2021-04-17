#include "aarch64.h"

#include <cstddef>

using namespace std;



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




