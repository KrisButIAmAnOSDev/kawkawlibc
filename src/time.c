#include "time.h"
#include "stdio.h"
#include "kawkawlibc.h"

#define CLOCK_PROCESS_CPUTIME_ID 2

time_t time(time_t *tloc)
{
    long ret = syscall(SYS_time, tloc);
    if (ret < 0) return (time_t)-1;
    if (tloc) *tloc = ret;
    return ret;
}

clock_t clock(void)
{
    struct timespec ts;
    if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts) < 0)
        return (clock_t)-1;
    return (clock_t)(ts.tv_sec * CLOCKS_PER_SEC + ts.tv_nsec / (1000000000 / CLOCKS_PER_SEC));
}

int clock_gettime(int clk_id, struct timespec *tp)
{
    return syscall(SYS_clock_gettime, clk_id, tp);
}

int gettimeofday(struct timeval *tv, void *tz)
{
    return syscall(SYS_gettimeofday, tv, tz);
}

int nanosleep(const struct timespec *req, struct timespec *rem)
{
    return syscall(SYS_nanosleep, req, rem);
}

double difftime(time_t time1, time_t time2)
{
    return (double)(time2 - time1);
}

struct tm *gmtime(const time_t *timer)
{
    static struct tm tm;
    time_t t = *timer;
    tm.tm_sec = t % 60; t /= 60;
    tm.tm_min = t % 60; t /= 60;
    tm.tm_hour = t % 24; t /= 24;
    tm.tm_year = 1970 + t / 365;
    tm.tm_mon = 0;
    tm.tm_mday = 1;
    tm.tm_wday = 0;
    tm.tm_yday = 0;
    tm.tm_isdst = 0;
    return &tm;
}

struct tm *localtime(const time_t *timer)
{
    return gmtime(timer);
}

time_t mktime(struct tm *tm)
{
    return (time_t)tm->tm_year * 365 + tm->tm_yday;
}

time_t timegm(struct tm *tm)
{
    return mktime(tm);
}

size_t strftime(char *s, size_t max, const char *format, const struct tm *tm)
{
    size_t len = 0;
    for (const char *p = format; *p && len < max - 1; p++) {
        if (*p == '%') {
            p++;
            switch (*p) {
            case 'Y': len += snprintf(s + len, max - len, "%d", tm->tm_year + 1900); break;
            case 'm': len += snprintf(s + len, max - len, "%02d", tm->tm_mon + 1); break;
            case 'd': len += snprintf(s + len, max - len, "%02d", tm->tm_mday); break;
            case 'H': len += snprintf(s + len, max - len, "%02d", tm->tm_hour); break;
            case 'M': len += snprintf(s + len, max - len, "%02d", tm->tm_min); break;
            case 'S': len += snprintf(s + len, max - len, "%02d", tm->tm_sec); break;
            case '%': s[len++] = '%'; break;
            default: s[len++] = '%'; s[len++] = *p; break;
            }
        } else {
            s[len++] = *p;
        }
    }
    s[len] = '\0';
    return len;
}