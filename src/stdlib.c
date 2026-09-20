#include "stdlib.h"
#include "string.h"
#include "kawkawlibc.h"

void abort(void)
{
    write(2, "abort\n", 6);
    exit(134);
}

void *malloc(size_t size)
{
    static void *heap_end = NULL;
    void *prev;

    if (size == 0) return NULL;
    size_t total = size + (8 - (size % 8)) % 8;

    if (heap_end == NULL) {
        heap_end = sbrk(4096);
        if (heap_end == (void *)-1) return NULL;
    }

    while ((char *)heap_end + total > (char *)brk(0)) {
        if (sbrk(4096) == (void *)-1) return NULL;
    }

    prev = heap_end;
    heap_end = (char *)heap_end + total;
    return prev;
}

void free(void *ptr)
{
    (void)ptr;
}

void *calloc(size_t count, size_t size)
{
    void *p = malloc(count * size);
    if (p) memset(p, 0, count * size);
    return p;
}

void *realloc(void *ptr, size_t size)
{
    void *new_p = malloc(size);
    if (new_p && ptr) {
        memcpy(new_p, ptr, size);
    }
    free(ptr);
    return new_p;
}

int atoi(const char *str)
{
    int result = 0;
    int sign = 1;
    while (*str == ' ') str++;
    if (*str == '-') { sign = -1; str++; }
    else if (*str == '+') { str++; }
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result * sign;
}

long atol(const char *str)
{
    long result = 0;
    int sign = 1;
    while (*str == ' ') str++;
    if (*str == '-') { sign = -1; str++; }
    else if (*str == '+') { str++; }
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result * sign;
}

long long atoll(const char *str)
{
    long long result = 0;
    int sign = 1;
    while (*str == ' ') str++;
    if (*str == '-') { sign = -1; str++; }
    else if (*str == '+') { str++; }
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result * sign;
}

double atof(const char *str)
{
    while (*str == ' ' || *str == '\t' || *str == '\n') str++;
    int sign = 1;
    if (*str == '-') { sign = -1; str++; }
    else if (*str == '+') { str++; }
    double result = 0.0;
    while (*str >= '0' && *str <= '9') {
        result = result * 10.0 + (*str - '0');
        str++;
    }
    if (*str == '.') {
        str++;
        double frac = 1.0;
        while (*str >= '0' && *str <= '9') {
            frac /= 10.0;
            result += (*str - '0') * frac;
            str++;
        }
    }
    if (*str == 'e' || *str == 'E') {
        str++;
        int exp_sign = 1;
        if (*str == '-') { exp_sign = -1; str++; }
        else if (*str == '+') { str++; }
        int exp = 0;
        while (*str >= '0' && *str <= '9') {
            exp = exp * 10 + (*str - '0');
            str++;
        }
        double mult = 1.0;
        for (int i = 0; i < exp; i++) mult *= 10.0;
        if (exp_sign < 0) result /= mult;
        else result *= mult;
    }
    return sign * result;
}

int abs(int j)
{
    return j < 0 ? -j : j;
}

long labs(long j)
{
    return j < 0 ? -j : j;
}

void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    if (nmemb <= 1)
        return;
    char *arr = (char *)base;
    for (size_t i = 1; i < nmemb; i++) {
        char tmp[size];
        memcpy(tmp, arr + i * size, size);
        size_t j = i;
        while (j > 0 && compar(arr + (j - 1) * size, tmp) > 0) {
            memcpy(arr + j * size, arr + (j - 1) * size, size);
            j--;
        }
        memcpy(arr + j * size, tmp, size);
    }
}

static unsigned int _rand_seed = 1;

int rand(void)
{
    _rand_seed = _rand_seed * 1103515245u + 12345u;
    return (int)((_rand_seed >> 16) & 0x7FFF);
}

void srand(unsigned int seed)
{
    _rand_seed = seed;
}

static int _digit(int c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    return -1;
}

long strtol(const char *nptr, char **endptr, int base)
{
    while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n') nptr++;
    int sign = 1;
    if (*nptr == '-') { sign = -1; nptr++; }
    else if (*nptr == '+') { nptr++; }
    long result = 0;
    if (base == 0) {
        if (*nptr == '0' && (nptr[1] == 'x' || nptr[1] == 'X')) { base = 16; nptr += 2; }
        else if (*nptr == '0') base = 8;
        else base = 10;
    }
    if (base < 2 || base > 36) base = 10;
    int d;
    while ((d = _digit(*nptr)) >= 0 && d < base) {
        result = result * base + d;
        nptr++;
    }
    if (endptr) *endptr = (char *)nptr;
    return sign * result;
}

unsigned long strtoul(const char *nptr, char **endptr, int base)
{
    while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n') nptr++;
    if (*nptr == '+') nptr++;
    unsigned long result = 0;
    if (base == 0) {
        if (*nptr == '0' && (nptr[1] == 'x' || nptr[1] == 'X')) { base = 16; nptr += 2; }
        else if (*nptr == '0') base = 8;
        else base = 10;
    }
    if (base < 2 || base > 36) base = 10;
    int d;
    while ((d = _digit(*nptr)) >= 0 && d < base) {
        result = result * base + d;
        nptr++;
    }
    if (endptr) *endptr = (char *)nptr;
    return result;
}

long long strtoll(const char *nptr, char **endptr, int base)
{
    while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n') nptr++;
    int sign = 1;
    if (*nptr == '-') { sign = -1; nptr++; }
    else if (*nptr == '+') { nptr++; }
    long long result = 0;
    if (base == 0) {
        if (*nptr == '0' && (nptr[1] == 'x' || nptr[1] == 'X')) { base = 16; nptr += 2; }
        else if (*nptr == '0') base = 8;
        else base = 10;
    }
    if (base < 2 || base > 36) base = 10;
    int d;
    while ((d = _digit(*nptr)) >= 0 && d < base) {
        result = result * base + d;
        nptr++;
    }
    if (endptr) *endptr = (char *)nptr;
    return sign * result;
}

unsigned long long strtoull(const char *nptr, char **endptr, int base)
{
    while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n') nptr++;
    if (*nptr == '+') nptr++;
    unsigned long long result = 0;
    if (base == 0) {
        if (*nptr == '0' && (nptr[1] == 'x' || nptr[1] == 'X')) { base = 16; nptr += 2; }
        else if (*nptr == '0') base = 8;
        else base = 10;
    }
    if (base < 2 || base > 36) base = 10;
    int d;
    while ((d = _digit(*nptr)) >= 0 && d < base) {
        result = result * base + d;
        nptr++;
    }
    if (endptr) *endptr = (char *)nptr;
    return result;
}

div_t div(int numer, int denom)
{
    div_t d;
    d.quot = numer / denom;
    d.rem = numer % denom;
    return d;
}

ldiv_t ldiv(long numer, long denom)
{
    ldiv_t d;
    d.quot = numer / denom;
    d.rem = numer % denom;
    return d;
}

static void (*_atexit_funcs[32])(void);
static int _atexit_count = 0;

int atexit(void (*func)(void))
{
    if (_atexit_count >= 32) return -1;
    _atexit_funcs[_atexit_count++] = func;
    return 0;
}

char *getenv(const char *name)
{
    (void)name;
    return NULL;
}

int system(const char *command)
{
    (void)command;
    return -1;
}
