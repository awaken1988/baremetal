#ifndef ARCH_ARM_COMMON_GIC_H_
#define ARCH_ARM_COMMON_GIC_H_

#include "../../typedefs.h"
#include "../../interrupt/interrupt.h"

namespace ns_arm_common {

	class Gic : public NsInterrupt::Interrupt
	{
	public:
		constexpr static u32_t GICC_CTLR 	= 0x000;
		constexpr static  u32_t GICC_PMR 	= 0x004;
		constexpr static  u32_t GICC_IAR 	= 0x00C;
		constexpr static  u32_t GICC_EOIR 	= 0x010;
		constexpr static  u32_t GICC_CTLR_ENABLEGRP0 	= (1 << 0);
		constexpr static  u32_t GICC_CTLR_ENABLEGRP1 	= (1 << 1);
		constexpr static  u32_t GICC_CTLR_FIQEN 		= (1 << 3);

		constexpr static  u32_t GICD_CTLR 	= 0x000;
		constexpr static  u32_t GICD_TYPER = 0x004;
		constexpr static  u32_t GICD_IGROUPR(u32_t n) 		{ return 0x080 + (n) * 4; };
		constexpr static  u32_t GICD_ISENABLER(u32_t n) 	{ return 0x100 + (n) * 4; };
		constexpr static  u32_t GICD_ICENABLER(u32_t n) 	{ return 0x180 + (n) * 4; };
		constexpr static  u32_t GICD_ISPENDR(u32_t n) 		{ return 0x200 + (n) * 4; };
		constexpr static  u32_t GICD_ICPENDR(u32_t n) 		{ return 0x280 + (n) * 4; };
		constexpr static  u32_t GICD_IPRIORITYR(u32_t n) 	{ return 0x400 + (n) * 4; };
		constexpr static  u32_t GICD_ITARGETSR(u32_t n) 	{ return 0x800 + (n) * 4; };
		constexpr static  u32_t GICD_SGIR = 0xF00;
		constexpr static  u32_t GICD_CTLR_ENABLEGRP0 =	(1 << 0);
		constexpr static  u32_t GICD_CTLR_ENABLEGRP1 =	(1 << 1);


		constexpr static size_t IRQ_MAX = 1020;
		constexpr static size_t IRQ_PER_LINE = 32;
	public:
		Gic();

		virtual void global_enable();
		virtual void global_disable();
		virtual void set_handler(int aIrqNum, std::function<void()> aHndler);
		virtual void set_enabled(int aIrqNum, bool aEnable);

	protected:
		bool check_irq_available(int aIrqNum);

	protected:
		bool m_security_extension;
		size_t m_line_numbers;

		bool m_irq_available[IRQ_MAX];
		bool m_irq_always_on[IRQ_MAX];

		std::function<void()> m_handler[IRQ_MAX];
	};



	extern uptr_t GIC_DIST_BASE;
	extern uptr_t GIC_CPU_BASE;
}

#endif /* ARCH_ARM_COMMON_GIC_H_ */
