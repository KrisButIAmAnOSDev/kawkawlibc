#include "stdlib.h"
#include "string.h"
#include "stdint.h"
#include "kawkawlibc.h"

extern char **environ;

typedef struct block {
    struct block *next;
    size_t size;
} block_t;

static block_t *free_list = NULL;

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

    /* try to reuse a freed block of sufficient size */
    block_t **pp = &free_list;
    while (*pp) {
        block_t *blk = *pp;
        if (blk->size >= total) {
            *pp = blk->next;             /* unlink from free list */
            if (blk->size >= total + sizeof(block_t) + 16) {
                /* split: carve off the tail into a new free block */
                block_t *rem = (block_t *)((char *)blk + total);
                rem->size = blk->size - total;
                rem->next = free_list;
                free_list = rem;
            }
            return (void *)(blk + 1);
        }
        pp = &blk->next;
    }

    if (heap_end == NULL) {
        heap_end = sbrk(4096);
        if (heap_end == (void *)-1) return NULL;
    }

    while ((char *)heap_end + total + sizeof(block_t) > (char *)brk(0)) {
        if (sbrk(4096) == (void *)-1) return NULL;
    }

    prev = heap_end;
    block_t *hdr = (block_t *)prev;
    hdr->size = total;
    heap_end = (char *)heap_end + total + sizeof(block_t);
    return (void *)(hdr + 1);
}

void free(void *ptr)
{
    if (!ptr) return;
    block_t *hdr = (block_t *)ptr - 1;
    hdr->next = free_list;
    free_list = hdr;
}

void *calloc(size_t count, size_t size)
{
    if (count && SIZE_MAX / count < size) return NULL;   /* overflow guard */
    void *p = malloc(count * size);
    if (p) memset(p, 0, count * size);
    return p;
}

void *realloc(void *ptr, size_t size)
{
    if (!ptr) return malloc(size);
    if (size == 0) { free(ptr); return NULL; }
    block_t *hdr = (block_t *)ptr - 1;
    size_t old_size = hdr->size;
    if (old_size >= size) return ptr;   /* block already big enough */
    void *new_p = malloc(size);
    if (!new_p) return NULL;
    memcpy(new_p, ptr, old_size);
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
    char *tmp = malloc(size);
    if (!tmp) return;
    for (size_t i = 1; i < nmemb; i++) {
        memcpy(tmp, arr + i * size, size);
        size_t j = i;
        while (j > 0 && compar(arr + (j - 1) * size, tmp) > 0) {
            memcpy(arr + j * size, arr + (j - 1) * size, size);
            j--;
        }
        memcpy(arr + j * size, tmp, size);
    }
    free(tmp);
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
    const char *start = nptr;
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
    if (nptr == start) {
        if (endptr) *endptr = (char *)(nptr - (sign == -1 ? 1 : 0));
        return 0;
    }
    if (endptr) *endptr = (char *)nptr;
    return sign * result;
}

unsigned long strtoul(const char *nptr, char **endptr, int base)
{
    while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n') nptr++;
    int sign = 0;
    if (*nptr == '-') { sign = -1; nptr++; }
    else if (*nptr == '+') { nptr++; }
    unsigned long result = 0;
    const char *start = nptr;
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
    if (nptr == start) {
        if (endptr) *endptr = (char *)(nptr - (sign == -1 ? 1 : 0));
        return 0;
    }
    if (endptr) *endptr = (char *)nptr;
    if (sign < 0) return 0UL - result;
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

double strtod(const char *nptr, char **endptr)
{
    while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n') nptr++;
    int sign = 1;
    if (*nptr == '-') { sign = -1; nptr++; }
    else if (*nptr == '+') { nptr++; }
    double result = 0.0;
    while (*nptr >= '0' && *nptr <= '9') {
        result = result * 10.0 + (*nptr - '0');
        nptr++;
    }
    if (*nptr == '.') {
        nptr++;
        double frac = 1.0;
        while (*nptr >= '0' && *nptr <= '9') {
            frac /= 10.0;
            result += (*nptr - '0') * frac;
            nptr++;
        }
    }
    if (*nptr == 'e' || *nptr == 'E') {
        nptr++;
        int exp_sign = 1;
        if (*nptr == '-') { exp_sign = -1; nptr++; }
        else if (*nptr == '+') { nptr++; }
        int exp = 0;
        while (*nptr >= '0' && *nptr <= '9') {
            exp = exp * 10 + (*nptr - '0');
            nptr++;
        }
        double mult = 1.0;
        for (int i = 0; i < exp; i++) mult *= 10.0;
        if (exp_sign < 0) result /= mult;
        else result *= mult;
    }
    if (endptr) *endptr = (char *)nptr;
    return sign * result;
}

float strtof(const char *nptr, char **endptr)
{
    return (float)strtod(nptr, endptr);
}

long double strtold(const char *nptr, char **endptr)
{
    return (long double)strtod(nptr, endptr);
}

static void (*_atexit_funcs[32])(void);
static int _atexit_count = 0;

int atexit(void (*func)(void))
{
    if (_atexit_count >= 32) return -1;
    _atexit_funcs[_atexit_count++] = func;
    return 0;
}

void *bsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    if (nmemb == 0) return NULL;
    const char *arr = (const char *)base;
    size_t lo = 0, hi = nmemb;
    while (lo < hi) {
        size_t mid = lo + (hi - lo) / 2;
        int cmp = compar(key, arr + mid * size);
        if (cmp == 0) return (void *)(arr + mid * size);
        if (cmp < 0) hi = mid;
        else lo = mid + 1;
    }
    return NULL;
}

char *getenv(const char *name)
{
    extern char **environ;
    size_t nlen = strlen(name);
    for (char **e = environ; e && *e; e++) {
        if (strncmp(*e, name, nlen) == 0 && (*e)[nlen] == '=')
            return *e + nlen + 1;
    }
    return NULL;
}

int system(const char *command)
{
    if (!command) return -1;
    pid_t pid = fork();
    if (pid < 0) return -1;
    if (pid == 0) {
        char *argv[] = {"/bin/sh", (char *)command, NULL};
        execve("/bin/sh", argv, environ);
        _exit(127);
    }
    int status;
    wait4(pid, &status, 0, NULL);
    return status;
}
