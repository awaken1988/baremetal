#ifndef CPU_H
#define CPU_H
#include "typedefs.h"

typedef enum
{
  IRQ_FLAG_F = 1<<6,
  IRQ_FLAG_I = 1<<7,
  IRQ_FLAG_A = 1<<8,
  IRQ_FLAG_D = 1<<9,
} interrupt_flag_t;



void cpu_irq_set(bool_t enable, interrupt_flag_t irq);



#endif /* CPU_H */
