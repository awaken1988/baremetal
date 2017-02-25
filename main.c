void print_uart0(const char *s);
void print_uart0_int(int);

int array[32];
int sum = 0;

int main()
{
  print_uart0("main() function\r\n");

  while(1) {
    sum += 1;

    if( 0 == (sum%0x100000) ) {
      asm volatile("svc #0");
    }
  }

  return 0;
}

//TODO: why is attribute ignored :-(
void __attribute(( interrupt_handler )) c_exception_el1h_syn()
{
  print_uart0("enter SYNCHRONIOUS EXCEPTION:  EL1h\r\n");
  print_uart0_int(sum);
  print_uart0("\r\n");
  print_uart0("leave SYNCHRONIOUS EXCEPTION:  EL1h\r\n");
  asm volatile("eret"); //workaround see above
}









//-----------------------------------------
// print to qemus console
//-----------------------------------------
volatile unsigned int * const UART0DR = (unsigned int *) 0x09000000;
void print_uart0(const char *s)
{
    while(*s != '\0') { 		/* Loop until end of string */
         *UART0DR = (unsigned int)(*s); /* Transmit char */
          s++;			        /* Next char */
    }
}

void print_uart0_int(int num)
{
  char buff[] = {'.', '.', '.', '.', '.', '.', '.', '.', 0};

  for(int i=0; i<sizeof(buff)-1; i++) {
    int curr = num>>(i*4) & 0xF;
    switch(curr) {
      case 0x0: buff[i] = '0'; break;
      case 0x1: buff[i] = '1'; break;
      case 0x2: buff[i] = '2'; break;
      case 0x3: buff[i] = '3'; break;
      case 0x4: buff[i] = '4'; break;
      case 0x5: buff[i] = '5'; break;
      case 0x6: buff[i] = '6'; break;
      case 0x7: buff[i] = '7'; break;
      case 0x8: buff[i] = '8'; break;
      case 0x9: buff[i] = '9'; break;
      case 0xA: buff[i] = 'A'; break;
      case 0xB: buff[i] = 'B'; break;
      case 0xC: buff[i] = 'C'; break;
      case 0xD: buff[i] = 'D'; break;
      case 0xE: buff[i] = 'E'; break;
      case 0xF: buff[i] = 'F'; break;
      default: buff[i] = '?'; break;
    }
  }

  print_uart0(buff);

}
