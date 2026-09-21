#include "threads.h"
#include "kawkawlibc.h"
#include "stdlib.h"
#include "time.h"

/* futex ops */
#define FUTEX_WAIT 0
#define FUTEX_WAKE 1
#define FUTEX_WAIT_BITSET 9
#define FUTEX_WAKE_BITSET 10

/* clone flags */
#define CLONE_VM        0x00000100
#define CLONE_FS        0x00000200
#define CLONE_FILES     0x00000400
#define CLONE_SIGHAND   0x00000800
#define CLONE_THREAD    0x00010000
#define CLONE_SYSVSEM   0x00004000
#define CLONE_SETTLS    0x00080000
#define CLONE_PARENT_SETTID 0x00100000
#define CLONE_CHILD_SETTID  0x00200000

static long sys_futex(int *uaddr, int op, int val, const struct timespec *timeout,
                      int *uaddr2, int val3)
{
    return syscall(SYS_futex, uaddr, op, val, timeout, uaddr2, val3);
}

static void _atomic_set(int *p, int v)
{
    __asm__ __volatile__("xchg %1, %0" : "+m"(*p) : "r"(v) : "memory");
}

static int _atomic_cmpxchg(int *p, int old, int newv)
{
    int res;
    __asm__ __volatile__("lock; cmpxchg %2, %1" : "=a"(res), "+m"(*p) : "r"(newv), "0"(old) : "memory");
    return res;
}

int thrd_create(thrd_t *thr, int (*func)(void *), void *arg)
{
    char *stack = malloc(16384);
    if (!stack) return thrd_nomem;
    int tid = 0;
    long ret = syscall(SYS_clone, CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND
                       | CLONE_THREAD | CLONE_SYSVSEM | CLONE_PARENT_SETTID
                       | CLONE_CHILD_SETTID,
                       stack + 16384, &tid, 0, 0);
    if (ret < 0) { free(stack); return thrd_error; }
    if (ret == 0) {
        int r = func(arg);
        syscall(SYS_exit, r);
    }
    *thr = (thrd_t)tid;
    return thrd_success;
}

int thrd_join(thrd_t thr, int *res)
{
    (void)thr;
    (void)res;
    return thrd_success;
}

void thrd_detach(thrd_t thr) { (void)thr; }

void thrd_yield(void)
{
    syscall(SYS_sched_yield);
}

int thrd_sleep(const struct timespec *dur, struct timespec *rem)
{
    return nanosleep(dur, rem);
}

int thrd_equal(thrd_t thr0, thrd_t thr1)
{
    return thr0 == thr1;
}

int mtx_init(mtx_t *mtx, int type)
{
    (void)type;
    *mtx = 0;
    return thrd_success;
}

void mtx_destroy(mtx_t *mtx) { (void)mtx; }

int mtx_lock(mtx_t *mtx)
{
    while (_atomic_cmpxchg(mtx, 0, 1) != 0) {
        while (*mtx != 0) {
            sys_futex(mtx, FUTEX_WAIT, 1, NULL, NULL, 0);
        }
    }
    return thrd_success;
}

int mtx_trylock(mtx_t *mtx)
{
    return _atomic_cmpxchg(mtx, 0, 1) == 0 ? thrd_success : thrd_busy;
}

int mtx_unlock(mtx_t *mtx)
{
    _atomic_set(mtx, 0);
    sys_futex(mtx, FUTEX_WAKE, 1, NULL, NULL, 0);
    return thrd_success;
}

void cnd_init(cnd_t *cond) { (void)cond; }

void cnd_destroy(cnd_t *cond) { (void)cond; }

void cnd_wait(cnd_t *cond, mtx_t *mtx)
{
    int seq = 0;
    (void)cond;
    sys_futex(&seq, FUTEX_WAIT, seq, NULL, NULL, 0);
    mtx_lock(mtx);
}

void cnd_broadcast(cnd_t *cond)
{
    (void)cond;
}

void cnd_signal(cnd_t *cond)
{
    (void)cond;
}

void call_once(once_flag *flag, void (*func)(void))
{
    if (func) func();
    (void)flag;
}

int tss_create(tss_t *key)
{
    (void)key;
    return thrd_nomem;
}

void tss_delete(tss_t key) { (void)key; }

void *tss_get(tss_t key)
{
    (void)key;
    return NULL;
}

int tss_set(tss_t key, const void *val)
{
    (void)key;
    (void)val;
    return thrd_nomem;
}