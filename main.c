void print_uart0(const char *s);



int main()
{
  int sum = 0;
  int addme = 0x100000;

  while(1) {
    sum += addme;
  }


  return 0;
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
