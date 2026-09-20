#ifndef KAWKAW_THREADS_H
#define KAWKAW_THREADS_H

#include "stdint.h"

typedef int thrd_t;
typedef int mtx_t;
typedef int cnd_t;
typedef int once_flag;
typedef int tss_t;

#define thrd_success 0
#define thrd_timedout 1
#define thrd_busy 2
#define thrd_error 3
#define thrd_nomem 4

#define mtx_plain     0
#define mtx_recursive 1
#define mtx_timed     2
#define mtx_timed_recursive 3

#define TSS_TLSKEYS 0

void call_once(once_flag *flag, void (*func)(void));
void cnd_wait(cnd_t *cond, mtx_t *mtx);
void cnd_broadcast(cnd_t *cond);
void cnd_signal(cnd_t *cond);
void cnd_destroy(cnd_t *cond);
void cnd_init(cnd_t *cond);
void mtx_destroy(mtx_t *mtx);
void mtx_init(mtx_t *mtx, int type);
int mtx_lock(mtx_t *mtx);
int mtx_trylock(mtx_t *mtx);
int mtx_unlock(mtx_t *mtx);
int thrd_create(thrd_t *thr, int (*func)(void *), void *arg);
int thrd_join(thrd_t thr, int *res);
void thrd_detach(thrd_t thr);
void thrd_sleep(const struct timespec *dur, struct timespec *rem);
void thrd_yield(void);
int thrd_equal(thrd_t thr0, thrd_t thr1);
void tss_delete(tss_t key);
int tss_create(tss_t *key);
void *tss_get(tss_t key);
int tss_set(tss_t key, const void *val);

#endif