#include "uchar.h"
#include "wchar.h"

size_t mbrtoc16(char16_t *dst, const char *src, size_t n, mbstate_t *ps)
{
    (void)ps;
    if (!src || n == 0) return 0;
    *dst = (char16_t)(unsigned char)src[0];
    return 1;
}

size_t c16rtomb(char *dst, char16_t src, mbstate_t *ps)
{
    (void)ps;
    if (!dst) return 0;
    *dst = (char)src;
    return 1;
}

size_t mbrtoc32(char32_t *dst, const char *src, size_t n, mbstate_t *ps)
{
    (void)ps;
    if (!src || n == 0) return 0;
    *dst = (char32_t)(unsigned char)src[0];
    return 1;
}

size_t c32rtomb(char *dst, char32_t src, mbstate_t *ps)
{
    (void)ps;
    if (!dst) return 0;
    *dst = (char)src;
    return 1;
}