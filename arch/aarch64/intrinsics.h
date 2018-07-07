#ifndef ARCH_AARCH64_INTRINSICS_H_
#define ARCH_AARCH64_INTRINSICS_H_

#include "../../typedefs.h"

namespace ns_arm_common {

	constexpr u32_t AARCH64_PSTATE_AIF_MASK = 0x1<<8 | 0x1<<7 | 0x1<<6;

	static inline void intr_irq_enable(bool aEnable)
	{
		u32_t val = 0;
		asm volatile("mrs %0, DAIF" : "=r"(val) : );

		if( aEnable ) {
			val &= ~AARCH64_PSTATE_AIF_MASK;
		}
		else {
			val |= AARCH64_PSTATE_AIF_MASK;
		}

		asm volatile("msr DAIF, x0" : : ""(val) :);
	}

}



#endif /* ARCH_AARCH64_INTRINSICS_H_ */
