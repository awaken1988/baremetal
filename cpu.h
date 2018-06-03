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

void gic_distributor_init(uptr_t base);
void gic_cpu_init(uptr_t base);

void gic_init(uptr_t dist_base, uptr_t cpu_base);
void gic_set_pending(uptr_t dist_base);
void gic_print_iar();


void cpu_timer_init();

void cpu_print_state();



//------------------------------
//asm commands for c usage
//------------------------------
u32_t mrs_current_el();
u32_t mrs_esr_el1();

void dbg_exception();


#endif /* CPU_H */
