#include "string.h"
#include "kawkawlibc.h"
#include "stdlib.h"

#if ENABLE_STRING
size_t strlen(const char *s)
{
    size_t len = 0;
    while (s[len])
        len++;
    return len;
}

void *memcpy(void *dest, const void *src, size_t n)
{
    char *d = dest;
    const char *s = src;

    if (n >= 8 && (uintptr_t)d % 8 == 0 && (uintptr_t)s % 8 == 0) {
        uint64_t *dl = (uint64_t *)d;
        const uint64_t *sl = (const uint64_t *)s;
        size_t words = n / 8;
        for (size_t i = 0; i < words; i++)
            dl[i] = sl[i];
        d += words * 8;
        s += words * 8;
        n -= words * 8;
    }

    for (size_t i = 0; i < n; i++)
        d[i] = s[i];
    return dest;
}

void *memset(void *s, int c, size_t n)
{
    char *p = s;

    if (n >= 8 && (uintptr_t)p % 8 == 0) {
        uint64_t *pl = (uint64_t *)p;
        uint64_t word = 0;
        for (size_t i = 0; i < 8; i++)
            ((char *)&word)[i] = (char)c;
        size_t words = n / 8;
        for (size_t i = 0; i < words; i++)
            pl[i] = word;
        p += words * 8;
        n -= words * 8;
    }

    for (size_t i = 0; i < n; i++)
        p[i] = (char)c;
    return s;
}

void *memmove(void *dest, const void *src, size_t n)
{
    char *d = dest;
    const char *s = src;
    if (d < s) {
        for (size_t i = 0; i < n; i++)
            d[i] = s[i];
    } else {
        for (size_t i = n; i > 0; i--)
            d[i - 1] = s[i - 1];
    }
    return dest;
}

int strcmp(const char *s1, const char *s2)
{
    size_t i = 0;
    while (s1[i] == s2[i]) {
        if (s1[i] == 0)
            return 0;
        i++;
    }
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}

char *strcpy(char *dest, const char *src)
{
    size_t i = 0;
    while ((dest[i] = src[i]) != 0)
        i++;
    return dest;
}

char *strncpy(char *dest, const char *src, size_t n)
{
    size_t i;
    for (i = 0; i < n && src[i] != 0; i++)
        dest[i] = src[i];
    for (; i < n; i++)
        dest[i] = 0;
    return dest;
}

char *strcat(char *dest, const char *src)
{
    size_t len = strlen(dest);
    strcpy(dest + len, src);
    return dest;
}

char *strncat(char *dest, const char *src, size_t n)
{
    size_t len = strlen(dest);
    strncpy(dest + len, src, n);
    return dest;
}

char *strchr(const char *s, int c)
{
    while (*s) {
        if (*s == (char)c)
            return (char *)s;
        s++;
    }
    if (c == 0)
        return (char *)s;
    return NULL;
}

char *strrchr(const char *s, int c)
{
    char *last = NULL;
    while (*s) {
        if (*s == (char)c)
            last = (char *)s;
        s++;
    }
    if (c == 0 && last)
        return last;
    if (c == 0)
        return (char *)s;
    return last;
}

char *strstr(const char *haystack, const char *needle)
{
    if (*needle == 0)
        return (char *)haystack;
    for (; *haystack; haystack++) {
        size_t i = 0;
        while (haystack[i] == needle[i] && needle[i] != 0)
            i++;
        if (needle[i] == 0)
            return (char *)haystack;
    }
    return NULL;
}

char *strerror(int errnum)
{
    static char buf[64];
    int start = 63;
    buf[start] = '\0';
    if (errnum == 0) {
        buf[--start] = '0';
    } else {
        unsigned long e = (unsigned long)errnum;
        while (e > 0) {
            buf[--start] = '0' + (e % 10);
            e /= 10;
        }
    }
    char msg[64] = "Error ";
    size_t msglen = 7;
    size_t numlen = 63 - start;
    for (size_t i = 0; i < numlen; i++)
        msg[msglen++] = buf[start + i];
    msg[msglen++] = '\n';
    write(2, msg, msglen - 1);
    return buf;
}

void *memchr(const void *s, int c, size_t n)
{
    const char *p = s;
    for (size_t i = 0; i < n; i++) {
        if (p[i] == (char)c)
            return (void *)(p + i);
    }
    return NULL;
}

char *strtok(char *str, const char *delim)
{
    static char *save = NULL;
    char *start;

    if (str) save = str;
    if (!save) return NULL;

    while (*save && strchr(delim, *save)) save++;
    if (*save == 0) { save = NULL; return NULL; }

    start = save;
    while (*save && !strchr(delim, *save)) save++;
    if (*save) { *save = 0; save++; }
    else save = NULL;
    return start;
}

size_t strspn(const char *s, const char *accept)
{
    size_t i = 0;
    while (s[i] && strchr(accept, s[i])) i++;
    return i;
}

size_t strcspn(const char *s, const char *reject)
{
    size_t i = 0;
    while (s[i] && !strchr(reject, s[i])) i++;
    return i;
}

char *strpbrk(const char *s, const char *accept)
{
    for (; *s; s++) {
        if (strchr(accept, *s))
            return (char *)s;
    }
    return NULL;
}
#endif

#if ENABLE_MALLOC
char *strdup(const char *s)
{
    size_t len = strlen(s);
    char *copy = malloc(len + 1);
    if (!copy) return NULL;
    strcpy(copy, s);
    return copy;
}
#endif
