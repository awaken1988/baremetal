#include <string>
#include <iostream>

#include "interface.h"
#include "aarch64.h"

volatile unsigned int* UART0 = (volatile unsigned int*)0x09000000;

int main()
{
    std::cout << "main:" << std::endl;

    mk_arch_prepare_scheduler();


    return 0;
}

