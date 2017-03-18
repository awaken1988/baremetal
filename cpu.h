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



#define GICD_CTLR(baseAddr)  				BASE_OFFSET_32(baseAddr, 0x000)
#define GICD_TYPER(baseAddr)  				BASE_OFFSET_32(baseAddr, 0x004)
#define GICD_ISENABLERn(baseAddr, irqIdx)  	BASE_OFFSET_32(baseAddr, (0x100 + irqIdx * 0x4))
#define GICD_ICENABLERn(baseAddr, irqIdx)  	BASE_OFFSET_32(baseAddr, (0x180 + irqIdx * 0x4))
#define GICD_IGROUPR(baseAddr, irqIdx)  	BASE_OFFSET_32(baseAddr, (0x080 + irqIdx * 0x4))
#define GICD_TARGETSR(baseAddr, irqIdx)  	BASE_OFFSET_32(baseAddr, (0x800 + irqIdx * 0x4))

#define GICC_CTRL(baseAddr)  				BASE_OFFSET_32(baseAddr, 0x000)
#define GICC_PMR(baseAddr)  				BASE_OFFSET_32(baseAddr, 0x004)

//#define GICD_CTLR		(0x000)
//#define GICD_TYPER		(0x004)
//#define GICD_IGROUPR(n)		(0x080 + (n) * 4)
//#define GICD_ISENABLER(n)	(0x100 + (n) * 4)
//#define GICD_ICENABLER(n)	(0x180 + (n) * 4)
//#define GICD_ISPENDR(n)		(0x200 + (n) * 4)
//#define GICD_ICPENDR(n)		(0x280 + (n) * 4)
//#define GICD_IPRIORITYR(n)	(0x400 + (n) * 4)
//#define GICD_ITARGETSR(n)	(0x800 + (n) * 4)
//#define GICD_SGIR	(0xF00)

//#define GICC_CTLR		(0x000)
//#define GICC_PMR		(0x004)
//#define GICC_IAR		(0x00C)
//#define GICC_EOIR	(0x010)



void cpu_irq_set(bool_t enable, interrupt_flag_t irq);

void gic_distributor_init(uptr_t base);
void gic_cpu_init(uptr_t base);

void cpu_timer_init();



#endif /* CPU_H */
