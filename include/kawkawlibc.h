#ifndef KAWKAWLIBC_H
#define KAWKAWLIBC_H

#include "stdint.h"
#include "stdarg.h"

typedef long ssize_t;
typedef long off_t;

struct stat;

extern long errno;

long syscall(long n, ...);

ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
int open(const char *path, int flags, ...);
int close(int fd);
off_t lseek(int fd, off_t offset, int whence);
size_t getcwd(char *buf, size_t size);
int stat(const char *path, struct stat *st);
__attribute__((__noreturn__)) void exit(int code);
void *brk(void *addr);
void *sbrk(intptr_t increment);

/* File access flags (Linux x86-64; change per kernel) */
#define O_RDONLY   0
#define O_WRONLY   1
#define O_RDWR     2
#define O_CREAT  0100
#define O_TRUNC  01000
#define O_APPEND 02000

/* lseek whence */
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#endif
