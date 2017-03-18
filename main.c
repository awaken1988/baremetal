#include "cpu.h"
#include "kernel_lib.h"

#define GIC_DIST_BASE 0x8000000
#define GIC_CPU_BASE 0x8010000


int array[32];
int sum = 0;

int main()
{
	gic_init(GIC_DIST_BASE, GIC_CPU_BASE);
	cpu_irq_set(ON, IRQ_FLAG_F | IRQ_FLAG_I);
	//cpu_timer_init();

	//gic_set_pending(GIC_DIST_BASE);
	while( true ) {

	}

	//test: enable/disable interrupt
	cpu_irq_set(ON, IRQ_FLAG_F | IRQ_FLAG_I);
	cpu_irq_set(OFF, IRQ_FLAG_F);


	//test print output
	k_print("main() function\r\n");
	k_print_ull(0x1122334455667788ull, PRINT_FLAG_HEX);
	k_print("\r\n");
	k_print_ull(0x1122334455667788ull, PRINT_FLAG_BIN);
	k_print("\r\n");

	//test memory allocation
	unsigned char* dynMem0 = k_malloc(16);
	unsigned char* dynMem1 = k_malloc(32);
	unsigned char* dynMem2 = k_malloc(64);
	k_free(dynMem1);
	unsigned char* dynMem4 = k_malloc(16);

	//test svc exception
	int i=0;
	while( 1 ) {
		sum++;
		if( (sum % 0x1000000) == 0 ) {
			asm volatile("svc #0");
		}
	}

	return 0;
}

//TODO: why is attribute ignored :-(
//  void __attribute(( interrupt_handler )) c_exception_el1h_syn()
void c_exception_el1h_syn()
{
	k_print("enter SYNCHRONIOUS EXCEPTION:  EL1h\r\n");
	k_print_ull(sum, PRINT_FLAG_HEX);
	k_print("\r\n");
	k_print("leave SYNCHRONIOUS EXCEPTION:  EL1h\r\n");
	asm volatile("eret"); //workaround see above
}
