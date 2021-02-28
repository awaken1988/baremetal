volatile unsigned int* UART0 = (volatile unsigned int*)0x10009000;

int main()
{
   int a = 0;
   int b = 1;

   for(int i=0; i<10; i++) {
       a = a + b;
       b++;
   }

    return 0;
}

