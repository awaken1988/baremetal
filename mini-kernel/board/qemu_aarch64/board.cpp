#include "board.h"

#include "aarch64.h"
#include "gic.h"

#define GIC_DIST_BASE 0x8000000
#define GIC_CPU_BASE  0x8010000

void mk_arch_prepare_scheduler()
{
	cpu_irq_set(ON, static_cast<interrupt_flag_t>(IRQ_FLAG_F | IRQ_FLAG_I) );
	cpu_timer_init();
	//gic_set_pending(GIC_DIST_BASE);
	gic_init(GIC_DIST_BASE, GIC_CPU_BASE);
	while( true ) {

	}
}

//--------------------------
//irq handlers
//--------------------------

extern "C" void currel_spx_irq__handle_iml()
{
	const iar_t iar = gic_start_irq(GIC_CPU_BASE);

	gic_end_irq(GIC_CPU_BASE, iar);
}

extern "C" void currel_spx_irq__handle()
{
	PUSH_CPUREGS

	__asm volatile(" bl currel_spx_irq__handle_iml");

	POP_CPUREGS
}


