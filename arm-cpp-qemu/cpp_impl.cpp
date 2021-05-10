#include <exception>
#include <stdlib.h>

[[noreturn]] void Terminate() noexcept
{
    // insert your own termination handler code here...
    while(1);
}

namespace __cxxabiv1
{
    std::terminate_handler __terminate_handler = Terminate;
}

void* operator new(size_t size)
{
    return malloc(size);
}

void operator delete(void* ptr)
{
   free(ptr);
}