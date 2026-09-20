#ifndef KAWKAW_SIGNAL_H
#define KAWKAW_SIGNAL_H

#include "stddef.h"
#include "sys/types.h"

typedef int sig_atomic_t;
typedef void (*sighandler_t)(int);
typedef unsigned long sigset_t;

#define SIG_DFL ((sighandler_t)0)
#define SIG_IGN ((sighandler_t)1)
#define SIG_ERR ((sighandler_t)-1)

#define SIGABRT 6
#define SIGFPE  8
#define SIGILL  4
#define SIGINT  2
#define SIGSEGV 11
#define SIGTERM 15
#define SIGKILL 9
#define SIGHUP  1
#define SIGQUIT 3
#define SIGBUS  7
#define SIGPIPE 13
#define SIGALRM 14
#define SIGUSR1 10
#define SIGUSR2 12
#define SIGCHLD 17
#define SIGCONT 18
#define SIGSTOP 19
#define SIGTSTP 20
#define SIGTTIN 21
#define SIGTTOU 22
#define SIGWINCH 28
#define SIGVTALRM 20
#define SIGPROF 27
#define SIGIO 29
#define SIGPWR 30
#define SIGSYS 31

#define NSIG 65

struct sigaction {
    sighandler_t sa_handler;
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer)(void);
};

#define SA_NOCLDSTOP  00000001
#define SA_RESTART    010000000000
#define SA_NODEFER    040000000
#define SA_RESETHAND  04000000

sighandler_t signal(int signum, sighandler_t handler);
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
int sigpending(sigset_t *set);
int sigsuspend(const sigset_t *mask);
int raise(int sig);
int kill(pid_t pid, int sig);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set, int signum);
int sigdelset(sigset_t *set, int signum);
int sigismember(const sigset_t *set, int signum);
int sigemptyset(sigset_t *set);

#endif