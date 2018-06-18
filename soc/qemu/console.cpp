#include "../../typedefs.h"



void k_dbg_putchar(const char aChar)
{
	volatile unsigned int * const UART0DR = (unsigned int *) 0x09000000;

	*UART0DR = (unsigned int)(aChar);
}
