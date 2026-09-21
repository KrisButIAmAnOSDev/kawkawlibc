#include "signal.h"
#include "kawkawlibc.h"

sighandler_t signal(int signum, sighandler_t handler)
{
    struct sigaction act, old;
    act.sa_handler = handler;
    act.sa_mask = 0;
    act.sa_flags = 0;
    if (sigaction(signum, &act, &old) < 0)
        return SIG_ERR;
    return old.sa_handler;
}

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)
{
    return syscall(SYS_sigaction, signum, act, oldact);
}

int sigprocmask(int how, const sigset_t *set, sigset_t *oldset)
{
    return syscall(SYS_rt_sigprocmask, how, set, oldset, 8);
}

int sigpending(sigset_t *set)
{
    (void)set;
    return 0;
}

int sigsuspend(const sigset_t *mask)
{
    (void)mask;
    return 0;
}

int raise(int sig)
{
    return kill(getpid(), sig);
}

int kill(pid_t pid, int sig)
{
    return syscall(SYS_kill, pid, sig);
}

int sigfillset(sigset_t *set)
{
    *set = (sigset_t)~0UL;
    return 0;
}

int sigaddset(sigset_t *set, int signum)
{
    *set |= (1UL << (signum - 1));
    return 0;
}

int sigdelset(sigset_t *set, int signum)
{
    *set &= ~(1UL << (signum - 1));
    return 0;
}

int sigismember(const sigset_t *set, int signum)
{
    return (*set & (1UL << (signum - 1))) ? 1 : 0;
}

int sigemptyset(sigset_t *set)
{
    *set = 0;
    return 0;
}