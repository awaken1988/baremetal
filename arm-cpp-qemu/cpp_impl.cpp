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

static int debug_allocated_size = 0;
void* operator new(size_t size)
{
    void* ret = NULL;

    ret = malloc(size);

    while(!ret) {
        __asm volatile("nop");
    }

    debug_allocated_size += size;

    return ret;
}

void operator delete(void* ptr)
{
   free(ptr);
}
