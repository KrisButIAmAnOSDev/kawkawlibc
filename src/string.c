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

int memcmp(const void *s1, const void *s2, size_t n)
{
    const unsigned char *p1 = s1;
    const unsigned char *p2 = s2;
    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i])
            return (int)(p1[i] - p2[i]);
    }
    return 0;
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

int strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i = 0;
    while (i < n && s1[i] == s2[i]) {
        if (s1[i] == 0)
            return 0;
        i++;
    }
    if (i == n)
        return 0;
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
    const char *last = NULL;
    while (*s) {
        if (*s == (char)c)
            last = s;
        s++;
    }
    if (c == 0)
        return (char *)s;
    return (char *)last;
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
    return buf + start;
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

char *strtok_r(char *str, const char *delim, char **saveptr)
{
    char *start;

    if (str) *saveptr = str;
    if (!*saveptr) return NULL;

    while (**saveptr && strchr(delim, **saveptr))
        (*saveptr)++;
    if (**saveptr == 0) { *saveptr = NULL; return NULL; }

    start = *saveptr;
    while (**saveptr && !strchr(delim, **saveptr))
        (*saveptr)++;
    if (**saveptr) {
        **saveptr = 0;
        (*saveptr)++;
    } else {
        *saveptr = NULL;
    }
    return start;
}

size_t strlcpy(char *dst, const char *src, size_t dsize)
{
    size_t i;
    if (dsize == 0) return strlen(src);
    for (i = 0; i < dsize - 1 && src[i]; i++)
        dst[i] = src[i];
    dst[i] = '\0';
    return strlen(src);
}

size_t strlcat(char *dst, const char *src, size_t dsize)
{
    size_t dlen = 0;
    size_t slen = strlen(src);
    while (dlen < dsize && dst[dlen]) dlen++;
    if (dlen == dsize) return dlen + slen;
    for (size_t i = 0; i < slen && dlen < dsize - 1; i++)
        dst[dlen++] = src[i];
    dst[dlen] = '\0';
    return dlen + slen;
}

void *memccpy(void *dst, const void *src, int c, size_t n)
{
    char *d = dst;
    const char *s = src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
        if (s[i] == (char)c)
            return (void *)(d + i + 1);
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

char *strndup(const char *s, size_t n)
{
    size_t len = 0;
    while (len < n && s[len]) len++;
    char *copy = malloc(len + 1);
    if (!copy) return NULL;
    memcpy(copy, s, len);
    copy[len] = '\0';
    return copy;
}
#endif
