#ifndef KAWKAW_STDLIB_H
#define KAWKAW_STDLIB_H

#include "stddef.h"

void abort(void);
void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t count, size_t size);
void *realloc(void *ptr, size_t size);
int atoi(const char *str);
long atol(const char *str);
double atof(const char *str);
void exit(int code);

#endif
