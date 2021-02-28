volatile unsigned int* UART0 = (volatile unsigned int*)0x10009000;

class MyClass 
{
public:
    MyClass() 
    {
        *UART0 = 'b';
    }
};


int main()
{
    MyClass x;

     *UART0 = 'a';

    while(1) {
         
    }

    return 0;
}

extern "C" {
    void exit(int status)
    {
       

        while(1);
    }
}

