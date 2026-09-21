#include "kawkawlibc.h"
#include <stdarg.h>
#include "stdnoreturn.h"

ssize_t read(int fd, void *buf, size_t count)
{
    return syscall(SYS_read, fd, buf, count);
}

ssize_t write(int fd, const void *buf, size_t count)
{
    return syscall(SYS_write, fd, buf, count);
}

int open(const char *path, int flags, ...)
{
    int mode = 0;
    if (flags & O_CREAT) {
        va_list ap;
        va_start(ap, flags);
        mode = va_arg(ap, int);
        va_end(ap);
    }
    return syscall(SYS_open, path, flags, mode);
}

int close(int fd)
{
    return syscall(SYS_close, fd);
}

off_t lseek(int fd, off_t offset, int whence)
{
    return syscall(SYS_lseek, fd, offset, whence);
}

size_t getcwd(char *buf, size_t size)
{
    return syscall(SYS_getcwd, buf, size);
}

int stat(const char *path, struct stat *st)
{
    return syscall(SYS_stat, path, st);
}

noreturn void exit(int code)
{
    syscall(SYS_exit, code);
    __builtin_unreachable();
}

void *brk(void *addr)
{
    return (void *)syscall(SYS_brk, (unsigned long)addr);
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