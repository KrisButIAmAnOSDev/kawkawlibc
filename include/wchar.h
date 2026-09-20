#ifndef KAWKAW_WCHAR_H
#define KAWKAW_WCHAR_H

#include "stddef.h"

typedef int wint_t;
typedef int wchar_t;

#define WEOF (-1)

size_t wcstombs(char *dst, const wchar_t *src, size_t max);
int mbstowcs(wchar_t *dst, const char *src, size_t max);
wint_t wcscoll(const wchar_t *s1, const wchar_t *s2);
size_t wcsxfrm(wchar_t *dst, const wchar_t *src, size_t max);
size_t wcslen(const wchar_t *s);
wchar_t *wcschr(const wchar_t *s, wint_t c);
wchar_t *wcsrchr(const wchar_t *s, wint_t c);
wchar_t *wcscpy(wchar_t *dst, const wchar_t *src);
wchar_t *wcsncpy(wchar_t *dst, const wchar_t *src, size_t n);
wchar_t *wcscat(wchar_t *dst, const wchar_t *src);
wchar_t *wcsncat(wchar_t *dst, const wchar_t *src, size_t n);
int wcscmp(const wchar_t *s1, const wchar_t *s2);
int wcsncmp(const wchar_t *s1, const wchar_t *s2, size_t n);
int wcscoll(const wchar_t *s1, const wchar_t *s2);
wchar_t *wcsstr(const wchar_t *haystack, const wchar_t *needle);
wchar_t *wcstok(wchar_t *str, const wchar_t *delim);
size_t wcscspn(const wchar_t *s, const wchar_t *reject);
size_t wcspn(const wchar_t *s, const wchar_t *accept);
wchar_t *wmemchr(const wchar_t *s, wint_t c, size_t n);
wchar_t *wmemcpy(wchar_t *dst, const wchar_t *src, size_t n);
wchar_t *wmemmove(wchar_t *dst, const wchar_t *src, size_t n);
wchar_t *wmemset(wchar_t *s, wint_t c, size_t n);

#endif