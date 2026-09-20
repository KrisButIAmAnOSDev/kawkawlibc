#ifndef KAWKAW_UNISTD_H
#define KAWKAW_UNISTD_H

#include "stddef.h"
#include "sys/types.h"

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define R_OK 4
#define W_OK 2
#define X_OK 1
#define F_OK 0

#define F_GETOWN  3
#define F_SETOWN  4
#define F_GETLK   5
#define F_SETLK   6
#define F_SETLKW  7
#define F_GETOWN_S 8
#define F_SETOWN_S 9

#define _exit(code) exit(code)

ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
int close(int fd);
int pipe(int fds[2]);
int dup(int fd);
int dup2(int oldfd, int newfd);
int fcntl(int fd, int cmd, ...);
int isatty(int fd);
int unlink(const char *pathname);
int rmdir(const char *pathname);
int mkdir(const char *pathname, mode_t mode);
int chdir(const char *path);
int fchdir(int fd);
int access(const char *pathname, int mode);
int link(const char *old, const char *new);
int symlink(const char *target, const char *linkpath);
ssize_t readlink(const char *path, char *buf, size_t bufsiz);
size_t getcwd(char *buf, size_t size);
pid_t fork(void);
pid_t getpid(void);
pid_t getppid(void);
uid_t getuid(void);
uid_t geteuid(void);
gid_t getgid(void);
gid_t getegid(void);
int execve(const char *path, char *const argv[], char *const envp[]);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
void _Exit(int status);
int pause(void);
int sleep(unsigned int seconds);
unsigned int alarm(unsigned int seconds);
int gethostname(char *name, size_t len);
int getdomainname(char *name, size_t len);
long sysconf(int name);
long pathconf(const char *path, int name);
long fpathconf(int fd, int name);

#endif