#ifndef KAWKAW_UCHAR_H
#define KAWKAW_UCHAR_H

#include "wchar.h"

typedef uint16_t char16_t;
typedef uint32_t char32_t;

size_t mbrtoc16(char16_t *dst, const char *src, size_t n, mbstate_t *ps);
size_t c16rtomb(char *dst, char16_t src, mbstate_t *ps);
size_t mbrtoc32(char32_t *dst, const char *src, size_t n, mbstate_t *ps);
size_t c32rtomb(char *dst, char32_t src, mbstate_t *ps);

#endif