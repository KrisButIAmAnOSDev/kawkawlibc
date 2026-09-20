#ifndef KAWKAW_STDLIB_H
#define KAWKAW_STDLIB_H

#include "kawkawlibc_config.h"
#include "stddef.h"

#if ENABLE_STDLIB

void abort(void);
void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t count, size_t size);
void *realloc(void *ptr, size_t size);
int atoi(const char *str);
long atol(const char *str);
long long atoll(const char *str);
double atof(const char *str);
void exit(int code);
int abs(int j);
long labs(long j);
void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

typedef struct { int quot; int rem; } div_t;
typedef struct { long quot; long rem; } ldiv_t;

div_t div(int numer, int denom);
ldiv_t ldiv(long numer, long denom);
long strtol(const char *nptr, char **endptr, int base);
unsigned long strtoul(const char *nptr, char **endptr, int base);
long long strtoll(const char *nptr, char **endptr, int base);
unsigned long long strtoull(const char *nptr, char **endptr, int base);
int rand(void);
void srand(unsigned int seed);

#endif

#endif