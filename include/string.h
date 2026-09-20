#ifndef KAWKAW_STRING_H
#define KAWKAW_STRING_H

#include "stdint.h"
#include "kawkawlibc_config.h"

#if ENABLE_STRING
size_t strlen(const char *s);
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, size_t n);
char *strchr(const char *s, int c);
char *strrchr(const char *s, int c);
char *strstr(const char *haystack, const char *needle);
char *strerror(int errnum);
void *memchr(const void *s, int c, size_t n);
char *strtok(char *str, const char *delim);
size_t strspn(const char *s, const char *accept);
size_t strcspn(const char *s, const char *reject);
char *strpbrk(const char *s, const char *accept);
#if ENABLE_MALLOC
char *strdup(const char *s);
#endif
#endif

#endif
