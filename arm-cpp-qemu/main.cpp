#include <array>




volatile unsigned int* UART0 = (volatile unsigned int*)0x10009000;


//Global
class GlobalTest
{
public:
    GlobalTest() 
    {
        *UART0 = 'c';
        m_a = 1;
        m_b = m_a + 1; 
    }
protected:
    int m_a;
    int m_b;
};

GlobalTest global_test;


//Simple Class
class MyClass 
{
public:
    MyClass() 
    {
        *UART0 = 'b';
    }
};

//Virtual class
class CBase 
{
public:
    virtual ~CBase() {

    }

    virtual void set() {
        m_val = 0x1;
        *UART0 = 'B';
    }

    int m_val = 0xcc;
};

class CDerived0 : public CBase
{
public:
    virtual void set() override {
        m_val = 0x2;
        *UART0 = '0';
    }
};

class CDerived1 : public CBase
{
public:
    virtual void set() override {
        m_val = 0x2;
        *UART0 = '1';
    }
};

int main()
{
    int* a = new int(1);

    MyClass x;

    *UART0 = 'a';

    while(1) {
        CBase* base0 = new CDerived0();
        CBase* base1 = new CDerived1();

        base0->set();
        base1->set();

        //throw 0xb33f;
    }

    return 0;
}

extern "C" {
    void exit(int status)
    {
        //TODO: print an error message
        while(1);
    }
}

