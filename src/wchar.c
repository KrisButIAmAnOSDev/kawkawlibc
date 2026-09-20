#include "wchar.h"

size_t wcslen(const wchar_t *s)
{
    size_t len = 0;
    while (s[len]) len++;
    return len;
}

wchar_t *wcschr(const wchar_t *s, wint_t c)
{
    while (*s) {
        if (*s == (wchar_t)c) return (wchar_t *)s;
        s++;
    }
    if (c == 0) return (wchar_t *)s;
    return NULL;
}

wchar_t *wcsrchr(const wchar_t *s, wint_t c)
{
    const wchar_t *last = NULL;
    while (*s) {
        if (*s == (wchar_t)c) last = s;
        s++;
    }
    if (c == 0) return (wchar_t *)s;
    return (wchar_t *)last;
}

wchar_t *wcscpy(wchar_t *dst, const wchar_t *src)
{
    size_t i = 0;
    while ((dst[i] = src[i]) != 0) i++;
    return dst;
}

wchar_t *wcsncpy(wchar_t *dst, const wchar_t *src, size_t n)
{
    size_t i;
    for (i = 0; i < n && src[i] != 0; i++)
        dst[i] = src[i];
    for (; i < n; i++)
        dst[i] = 0;
    return dst;
}

wchar_t *wcscat(wchar_t *dst, const wchar_t *src)
{
    size_t len = wcslen(dst);
    wcscpy(dst + len, src);
    return dst;
}

wchar_t *wcsncat(wchar_t *dst, const wchar_t *src, size_t n)
{
    size_t len = wcslen(dst);
    size_t i;
    for (i = 0; i < n && src[i] != 0; i++)
        dst[len + i] = src[i];
    dst[len + i] = 0;
    return dst;
}

int wcscmp(const wchar_t *s1, const wchar_t *s2)
{
    while (*s1 == *s2) {
        if (*s1 == 0) return 0;
        s1++;
        s2++;
    }
    return (int)(unsigned short)*s1 - (int)(unsigned short)*s2;
}

int wcsncmp(const wchar_t *s1, const wchar_t *s2, size_t n)
{
    size_t i = 0;
    while (i < n && s1[i] == s2[i]) {
        if (s1[i] == 0) return 0;
        i++;
    }
    if (i == n) return 0;
    return (int)(unsigned short)s1[i] - (int)(unsigned short)s2[i];
}

wchar_t *wcsstr(const wchar_t *haystack, const wchar_t *needle)
{
    if (*needle == 0) return (wchar_t *)haystack;
    for (; *haystack; haystack++) {
        size_t i = 0;
        while (haystack[i] == needle[i] && needle[i] != 0) i++;
        if (needle[i] == 0) return (wchar_t *)haystack;
    }
    return NULL;
}

wchar_t *wcstok(wchar_t *str, const wchar_t *delim)
{
    static wchar_t *save = NULL;
    wchar_t *start;

    if (str) save = str;
    if (!save) return NULL;

    while (*save && wcschr(delim, *save)) save++;
    if (*save == 0) { save = NULL; return NULL; }

    start = save;
    while (*save && !wcschr(delim, *save)) save++;
    if (*save) { *save = 0; save++; }
    else save = NULL;
    return start;
}

size_t wcscspn(const wchar_t *s, const wchar_t *reject)
{
    size_t i = 0;
    while (s[i] && !wcschr(reject, s[i])) i++;
    return i;
}

size_t wcspn(const wchar_t *s, const wchar_t *accept)
{
    size_t i = 0;
    while (s[i] && wcschr(accept, s[i])) i++;
    return i;
}

wchar_t *wmemchr(const wchar_t *s, wint_t c, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        if (s[i] == (wchar_t)c) return (wchar_t *)(s + i);
    }
    return NULL;
}

wchar_t *wmemcpy(wchar_t *dst, const wchar_t *src, size_t n)
{
    for (size_t i = 0; i < n; i++) dst[i] = src[i];
    return dst;
}

wchar_t *wmemmove(wchar_t *dst, const wchar_t *src, size_t n)
{
    if (dst < src) {
        for (size_t i = 0; i < n; i++) dst[i] = src[i];
    } else {
        for (size_t i = n; i > 0; i--) dst[i - 1] = src[i - 1];
    }
    return dst;
}

wchar_t *wmemset(wchar_t *s, wint_t c, size_t n)
{
    for (size_t i = 0; i < n; i++) s[i] = (wchar_t)c;
    return s;
}

size_t wcstombs(char *dst, const wchar_t *src, size_t max)
{
    size_t i = 0;
    while (src[i] && i < max) {
        dst[i] = (char)src[i];
        i++;
    }
    if (i < max) dst[i] = '\0';
    return i;
}

int mbstowcs(wchar_t *dst, const char *src, size_t max)
{
    size_t i = 0;
    while (src[i] && i < max) {
        dst[i] = (wchar_t)(unsigned char)src[i];
        i++;
    }
    return (int)i;
}