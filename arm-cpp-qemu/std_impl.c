#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <stdio.h>

static volatile unsigned int* UART0 = (volatile unsigned int*)0x09000000;

_READ_WRITE_RETURN_TYPE _write(int fd, const void *buf, size_t count)
{
    while(count > 0) {
        *UART0 = *((char*)buf);
        buf++;
        count--;
    }

    return 0;
}

_READ_WRITE_RETURN_TYPE _read(int fd, void *buf, size_t count)
{
    return 0;
}

int _open(const char *path, int oflags)
{
    return 0;
}

off_t _lseek(int fd, off_t offset, int whence)
{

}

int _kill(pid_t pid, int sig)
{
    return 0;
}

int _isatty(int fd)
{
    return 0;
}

int _close(int fd)
{
    return 0;
}

//int _fstat(int fd, struct stat *buf)
//{
//    return 0;
//}

int brk(void *addr)
{
    return 0;
}

extern void* heap_start;
extern void* heap_end;
void* _sbrk(intptr_t increment)
{
    static uint8_t* heap_current = (uint8_t*)&heap_start;
    uint8_t*  end = (uint8_t*)&heap_end;

    if( (heap_current+increment) > end ) {
        errno = ENOMEM;
        return (void*)-1;
    }

    uint8_t* old_current = heap_current;
    heap_current += increment;

    return old_current;
}

void _exit(int status)
{
    while(1);
}

pid_t _getpid(void)
{
    return 0;
}




//---------------------------
// printf stuff
//---------------------------
int fprintf (FILE *__restrict __stream,
                __const char *__restrict __format, ...)
{
    return 0;
}

int fputs (__const char *__restrict __s, FILE *__restrict
__stream)
{
    return 0;
}

int printf (__const char *__restrict __format, ...)
{
    return 0;
}

int puts (__const char *__s)
{
    return 0;
}