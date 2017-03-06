#include "cpu.h"



void cpu_irq_set(bool_t enable, interrupt_flag_t irq)
{
  volatile uint32_t msr_val = 0;

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
