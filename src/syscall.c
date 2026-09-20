#include "kawkawlibc.h"
#include "stat.h"
#include <stdarg.h>
#include "stdnoreturn.h"

ssize_t read(int fd, void *buf, size_t count)
{
    return syscall(0, fd, buf, count);
}

ssize_t write(int fd, const void *buf, size_t count)
{
    return syscall(1, fd, buf, count);
}

int open(const char *path, int flags, ...)
{
    va_list ap;
    va_start(ap, flags);
    int mode = va_arg(ap, int);
    va_end(ap);
    return syscall(2, path, flags, mode);
}

int close(int fd)
{
    return syscall(3, fd);
}

off_t lseek(int fd, off_t offset, int whence)
{
    return syscall(8, fd, offset, whence);
}

size_t getcwd(char *buf, size_t size)
{
    return syscall(79, buf, size);
}

int stat(const char *path, struct stat *st)
{
    return syscall(4, path, st);
}

noreturn void exit(int code)
{
    syscall(60, code);
    __builtin_unreachable();
}

void *brk(void *addr)
{
    return (void *)syscall(12, (unsigned long)addr);
}

void *sbrk(intptr_t increment)
{
    void *current = brk(0);
    if (current == (void *)-1) return (void *)-1;
    void *new_addr = (char *)current + increment;
    void *result = brk(new_addr);
    if (result == (void *)-1) return (void *)-1;
    return current;
}
