#ifndef KAWKAWLIBC_H
#define KAWKAWLIBC_H

#include "stdint.h"
#include "stdarg.h"

typedef long ssize_t;
typedef long off_t;
typedef int pid_t;

extern char **environ;

struct stat {
    unsigned long  st_dev;
    unsigned long  st_ino;
    unsigned long  st_nlink;
    unsigned int   st_mode;
    unsigned int   st_uid;
    unsigned int   st_gid;
    unsigned int   __pad0;
    unsigned long  st_rdev;
    long           st_size;
    long           st_blksize;
    long           st_blocks;
};

#define S_ISREG(m)  (((m) & 0170000) == 0100000)
#define S_ISDIR(m)  (((m) & 0170000) == 0040000)
#define S_ISCHR(m)  (((m) & 0170000) == 0020000)
#define S_ISBLK(m)  (((m) & 0170000) == 0060000)
#define S_ISFIFO(m) (((m) & 0170000) == 0010000)
#define S_ISLNK(m)  (((m) & 0170000) == 0120000)
#define S_ISSOCK(m) (((m) & 0170000) == 0140000)

#define S_IFMT     0170000
#define S_IFCHR   0020000
#define S_IFBLK   0060000
#define S_IFIFO   0010000
#define S_IFLNK   0120000
#define S_IFSOCK  0140000

#define O_RDONLY   0
#define O_WRONLY   1
#define O_RDWR     2
#define O_CREAT  0100
#define O_TRUNC  01000
#define O_APPEND 02000

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
int getpid(void);
int fork(void);
int execve(const char *path, char *const argv[], char *const envp[]);
int wait4(pid_t pid, int *wstatus, int options, void *rusage);

/* lseek whence */
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

/* Linux x86-64 syscall numbers */
#define SYS_read         0
#define SYS_write        1
#define SYS_open         2
#define SYS_close        3
#define SYS_stat         4
#define SYS_fstat        5
#define SYS_lstat        6
#define SYS_lseek        8
#define SYS_brk          12
#define SYS_getcwd       79
#define SYS_getpid       39
#define SYS_getuid       23
#define SYS_getgid       24
#define SYS_geteuid      107
#define SYS_getegid      108
#define SYS_gettid       186
#define SYS_gettimeofday 96
#define SYS_nanosleep    35
#define SYS_time         201
#define SYS_clock_gettime 228
#define SYS_uname        63
#define SYS_unlink       87
#define SYS_rename       82
#define SYS_mkdir        83
#define SYS_rmdir        84
#define SYS_access       21
#define SYS_fcntl        72
#define SYS_dup          32
#define SYS_dup2         33
#define SYS_pipe         22
#define SYS_fchdir       81
#define SYS_readlink     89
#define SYS_symlink      88
#define SYS_link         86
#define SYS_kill         62
#define SYS_wait4        61
#define SYS_fork         57
#define SYS_execve       59
#define SYS_sigaction    13
#define SYS_rt_sigaction 13
#define SYS_rt_sigprocmask 14
#define SYS_signal       13
#define SYS_arch_prctl   157
#define SYS_sched_yield   24
#define SYS_getrandom    318
#define SYS_statx        332
#define SYS_exit         60
#define SYS_exit_group   231
#define SYS_clone        56
#define SYS_fork         57
#define SYS_futex        202
#define SYS_sched_yield   24
#define SYS_set_tid_address 218
#define SYS_gettid       186

#endif
