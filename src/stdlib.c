#include "stdlib.h"
#include "string.h"
#include "kawkawlibc.h"

void *malloc(size_t size)
{
    static void *heap_end = NULL;
    void *prev;
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

double atof(const char *str)
{
    (void)str;
    return 0.0;
}
