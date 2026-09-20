#ifndef KAWKAW_TIME_H
#define KAWKAW_TIME_H

#include "stddef.h"

typedef long time_t;
typedef long clock_t;
typedef long suseconds_t;

struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};

struct timespec {
    time_t tv_sec;
    long tv_nsec;
};

struct itimerval {
    struct timeval it_interval;
    struct timeval it_value;
};

struct timeval {
    time_t tv_sec;
    suseconds_t tv_usec;
};

#define CLOCKS_PER_SEC 1000000

time_t time(time_t *tloc);
clock_t clock(void);
double difftime(time_t time1, time_t time2);
time_t mktime(struct tm *tm);
struct tm *gmtime(const time_t *timer);
struct tm *localtime(const time_t *timer);
size_t strftime(char *s, size_t max, const char *format, const struct tm *tm);
time_t timegm(struct tm *tm);
int nanosleep(const struct timespec *req, struct timespec *rem);
int clock_gettime(int clk_id, struct timespec *tp);
int gettimeofday(struct timeval *tv, void *tz);

#endif