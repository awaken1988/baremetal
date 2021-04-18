#ifndef AARCH64_H
#define AARCH64_H

#include "mk_types.h"

typedef enum
{
  IRQ_FLAG_F = 1<<6,
  IRQ_FLAG_I = 1<<7,
  IRQ_FLAG_A = 1<<8,
  IRQ_FLAG_D = 1<<9,
} interrupt_flag_t;

#define GICC_CTLR		(0x000)
#define GICC_PMR		(0x004)
#define GICC_IAR		(0x00C)
#define GICC_EOIR		(0x010)
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
#define GICC_CTLR_ENABLEGRP0	(1 << 0)
#define GICC_CTLR_ENABLEGRP1	(1 << 1)
#define GICC_CTLR_FIQEN		    (1 << 3)
#define GICD_CTLR_ENABLEGRP0	(1 << 0)
#define GICD_CTLR_ENABLEGRP1	(1 << 1)


uint32_t mrs_current_el();

void cpu_irq_set(bool enable, interrupt_flag_t irq);
void cpu_timer_init();
void cpu_print_state();

#define PUSH_CPUREGS \
  __asm volatile("stp	x29, x30, [sp, #-16]!"); \
  __asm volatile("stp	x27, x28, [sp, #-16]!"); \
  __asm volatile("stp	x25, x26, [sp, #-16]!"); \
  __asm volatile("stp	x23, x24, [sp, #-16]!"); \
  __asm volatile("stp	x21, x22, [sp, #-16]!"); \
  __asm volatile("stp	x19, x20, [sp, #-16]!"); \
  __asm volatile("stp	x17, x18, [sp, #-16]!"); \
  __asm volatile("stp	x15, x16, [sp, #-16]!"); \
  __asm volatile("stp	x13, x14, [sp, #-16]!"); \
  __asm volatile("stp	x11, x12, [sp, #-16]!"); \
  __asm volatile("stp	x9, x10, [sp, #-16]! "); \
  __asm volatile("stp	x7, x8, [sp, #-16]!  "); \
  __asm volatile("stp	x5, x6, [sp, #-16]!  "); \
  __asm volatile("stp	x3, x4, [sp, #-16]!  "); \
  __asm volatile("stp	x1, x2, [sp, #-16]!  ");

#define POP_CPUREGS \
  __asm volatile("ldp	x1, x2, [sp], #16  "); \
  __asm volatile("ldp	x3, x4, [sp], #16  "); \
  __asm volatile("ldp	x5, x6, [sp], #16  "); \
  __asm volatile("ldp	x7, x8, [sp], #16  "); \
  __asm volatile("ldp	x9, x10, [sp], #16 "); \
  __asm volatile("ldp	x11, x12, [sp], #16"); \
  __asm volatile("ldp	x13, x14, [sp], #16"); \
  __asm volatile("ldp	x15, x16, [sp], #16"); \
  __asm volatile("ldp	x17, x18, [sp], #16"); \
  __asm volatile("ldp	x19, x20, [sp], #16"); \
  __asm volatile("ldp	x21, x22, [sp], #16"); \
  __asm volatile("ldp	x23, x24, [sp], #16"); \
  __asm volatile("ldp	x25, x26, [sp], #16"); \
  __asm volatile("ldp	x27, x28, [sp], #16"); \
  __asm volatile("ldp	x29, x30, [sp], #16"); 


#endif // AARCH64_H