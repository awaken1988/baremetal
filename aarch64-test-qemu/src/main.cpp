#include <string>
#include <iostream>

volatile unsigned int* UART0 = (volatile unsigned int*)0x10009000;

class Test
{
public:
    Test(int aNum)
    {
        m_num = aNum;
        m_num++;
    }

    int get() const
    {
        return m_num;
    }

    int m_num;
};

Test mytest(3);


int main()
{
    int a = mytest.get();

    a++;

    std::cout << "bla" << std::endl;

    while(1);

    return 0;
}

