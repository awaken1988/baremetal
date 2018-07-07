#include "util/print.h"

#include "arch/arm_common/gic.h"

class CTest {
public:
	int a;
	int b;
	int c;
};

#define  STRINGIFY2(x) STRINGIFY(x)
#define STRINGIFY(x) #x

int main()
{
	ns_util::console("--------------------------------------------------").nl();
	ns_util::console("- SimpleBaremetalOS ARCH=% SOC=%")
		.arg_str(STRINGIFY2(ARCH))
		.arg_str(STRINGIFY2(SOC)).nl();
	ns_util::console("---------------------------------------------------").nl();

	NsInterrupt::Interrupt* irq = new ns_arm_common::Gic();

	irq->set_handler(0, []() -> void {return;});


	ns_util::console("\r\n");
	ns_util::console("\r\n");
	ns_util::console("").nl();
	ns_util::console("Debug output Test \r\n");

	ns_util::console(": hex=%; bin=%    \r\n")
		.arg_num(0xAFFE, num_format_e::HEX)
		.arg_num(0xAFFE, num_format_e::BINARY);

	ns_util::console(": hex=%; bin=%    \r\n")
			.arg_num(0x12345678abcdefULL, num_format_e::HEX)
			.arg_num(0x12345678abcdefULL, num_format_e::BINARY);


	while( 1 ) {
	}

	return 0;
}

//TODO: why is attribute ignored :-(
//  void __attribute(( interrupt_handler )) c_exception_el1h_syn()
void c_exception_el1h_syn()
{

	asm volatile("eret"); //workaround see above
}

void c_exception_el1h_irq()
{
	asm volatile("nop");



	asm volatile("eret"); //workaround see above
}

