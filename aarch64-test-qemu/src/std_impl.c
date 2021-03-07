#include <unistd.h>

static volatile unsigned int* UART0 = (volatile unsigned int*)0x10009000;

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

int _fstat(int fd, struct stat *buf)
{
    return 0;
}

int brk(void *addr)
{
    return 0;
}

void* _sbrk(intptr_t increment)
{
    
}

void _exit(int status)
{

}

pid_t _getpid(void)
{
    return 0;
}