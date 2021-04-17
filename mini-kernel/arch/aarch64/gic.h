#ifndef GIC_H
#define GIC_H

#include "mk_types.h"


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


void gic_init(uptr_t dist_base, uptr_t cpu_base);
void gic_enable_irq(uptr_t dist_base);
void gic_set_pending(uintptr_t dist_base);

#endif // GIC_H