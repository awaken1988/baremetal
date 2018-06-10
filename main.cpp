int array[32];
int sum = 0;

int main()
{
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

