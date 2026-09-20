#ifndef KAWKAW_FCNTL_H
#define KAWKAW_FCNTL_H

#include "sys/types.h"

#define O_RDONLY    00000000
#define O_WRONLY    00000001
#define O_RDWR      00000002
#define O_CREAT     00000100
#define O_EXCL      00000200
#define O_TRUNC     00001000
#define O_APPEND    00002000
#define O_NONBLOCK  00004000
#define O_NDELAY    00004000
#define O_SYNC      0004010000
#define O_DSYNC     0000010000
#define O_FSYNC     0004010000
#define O_DIRECTORY 00200000
#define O_NOFOLLOW   00400000
#define O_CLOEXEC    02000000

#define F_GETFL    3
#define F_SETFL    4
#define F_GETFD    5
#define F_SETFD    6
#define F_DUPFD    10
#define F_DUPFD_CLOEXEC 1024

#define FD_CLOEXEC 1

#define F_RDLCK  0
#define F_WRLCK  1
#define F_UNLCK  2

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define LOCK_SH 1
#define LOCK_EX 2
#define LOCK_NB  4
#define LOCK_UN 8

#define POSIX_FADV_DONTNEED 3
#define POSIX_FADV_NOREUSE 11
#define POSIX_FADV_SEQUENTIAL 2
#define POSIX_FADV_RANDOM 1
#define POSIX_FADV_WILLNEED 3

int open(const char *path, int flags, ...);
int openat(int dirfd, const char *path, int flags, ...);
int creat(const char *path, mode_t mode);
int fcntl(int fd, int cmd, ...);
int lockf(int fd, int cmd, off_t len);

#endif