#ifndef ARCH_ARM_COMMON_GIC_H_
#define ARCH_ARM_COMMON_GIC_H_

#include "../../typedefs.h"

namespace ns_arm_common {
	constexpr  u32_t GICC_CTLR 	= 0x000;
	constexpr  u32_t GICC_PMR 	= 0x004;
	constexpr  u32_t GICC_IAR 	= 0x00C;
	constexpr  u32_t GICC_EOIR 	= 0x010;
	constexpr  u32_t GICC_CTLR_ENABLEGRP0 	= (1 << 0);
	constexpr  u32_t GICC_CTLR_ENABLEGRP1 	= (1 << 1);
	constexpr  u32_t GICC_CTLR_FIQEN 		= (1 << 3);

	constexpr  u32_t GICD_CTLR 	= 0x000;
	constexpr  u32_t GICD_TYPER = 0x004;
	constexpr  u32_t GICD_IGROUPR(u32_t n) 		{ return 0x080 + (n) * 4; };
	constexpr  u32_t GICD_ISENABLER(u32_t n) 	{ return 0x100 + (n) * 4; };
	constexpr  u32_t GICD_ICENABLER(u32_t n) 	{ return 0x180 + (n) * 4; };
	constexpr  u32_t GICD_ISPENDR(u32_t n) 		{ return 0x200 + (n) * 4; };
	constexpr  u32_t GICD_ICPENDR(u32_t n) 		{ return 0x280 + (n) * 4; };
	constexpr  u32_t GICD_IPRIORITYR(u32_t n) 	{ return 0x400 + (n) * 4; };
	constexpr  u32_t GICD_ITARGETSR(u32_t n) 	{ return 0x800 + (n) * 4; };
	constexpr  u32_t GICD_SGIR = 0xF00;
	constexpr  u32_t GICD_CTLR_ENABLEGRP0 =	(1 << 0);
	constexpr  u32_t GICD_CTLR_ENABLEGRP1 =	(1 << 1);

	extern uptr_t GIC_DIST_BASE;
	extern uptr_t GIC_CPU_BASE;

	void gic_init();
}

#endif /* ARCH_ARM_COMMON_GIC_H_ */
