#include <array>
#include <memory>
#include <array>
#include <list>



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
        m_val = 0x3;
        *UART0 = '1';
    }
};

constexpr size_t array_size = 4;

void simple_ptr_array()
{
    #if ARRAY_METHOD == 1
        std::array<CBase*, array_size> base_array = {nullptr, nullptr, nullptr, nullptr};
	#else
        CBase* base_array[array_size];
    #endif

    for(int i=0; i<array_size; i++) {
        if( i%2 == 0 ) {
            base_array[i] = new CDerived0;
        }
        else {
            base_array[i] = new CDerived1;
        }
    }

    for(int i=0; i<array_size; i++) {
        base_array[i]->set();
    }

     for(int i=0; i<array_size; i++) {
         int test = base_array[i]->m_val;
     }
}

void simple_stdlist()
{
	std::list<int> mylist;

	mylist.push_back(1);
    mylist.push_back(2);
    mylist.push_back(3);
    mylist.push_back(4);
}

void simple_sharedptr_array()
{
   std::array<std::shared_ptr<CBase>, array_size> base_array;

    for(int i=0; i<array_size; i++) {
        if( i%2 == 0 ) {
            base_array[i] = std::shared_ptr<CBase>(new CDerived1);
        }
        else {
            base_array[i] = std::shared_ptr<CBase>(new CDerived0);
        }
    }

    for(int i=0; i<array_size; i++) {
        base_array[i]->set();
    }

     for(int i=0; i<array_size; i++) {
         int test = base_array[i]->m_val;
     }
}

int main()
{
    int* a = new int(1);

    MyClass x;

    *UART0 = 'a';

    simple_ptr_array();
    simple_sharedptr_array();
    simple_stdlist();

    //list


    return 0;
}

extern "C" {
    void exit(int status)
    {
        //TODO: print an error message
        while(1);
    }
}

