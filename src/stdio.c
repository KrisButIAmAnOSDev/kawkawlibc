#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <kawkawlibc.h>

// most important file in human history ig 

static FILE _stdin = { .fd = 0, .mode = 1, .eof = 0, .error = 0 };
static FILE _stdout = { .fd = 1, .mode = 0, .eof = 0, .error = 0 };
static FILE _stderr = { .fd = 2, .mode = 0, .eof = 0, .error = 0 };

FILE *stdin = &_stdin;
FILE *stdout = &_stdout;
FILE *stderr = &_stderr;

static void put_char_fd(int fd, char c) { write(fd, &c, 1); }

static void put_uint_fd(int fd, unsigned long long val, const char *digits, int base)
{
    char buf[64];
    char *p = buf + 64;
    *--p = '\0';
    if (val == 0) { *--p = '0'; }
    else { while (val > 0) { *--p = digits[val % (unsigned long long)base]; val /= base; } }
    write(fd, p, strlen(p));
}

static void put_int_fd(int fd, long long val)
{
    unsigned long long uval;
    if (val < 0) { put_char_fd(fd, '-'); uval = 0 - (unsigned long long)val; }
    else { uval = (unsigned long long)val; }
    put_uint_fd(fd, uval, "0123456789", 10);
}

static void put_pad_fd(int fd, int n, char c)
{
    while (n-- > 0) put_char_fd(fd, c);
}

static void format_fd(int fd, const char *fmt, va_list ap)
{
    for (const char *p = fmt; *p; p++) {
        if (*p != '%') { put_char_fd(fd, *p); continue; }
        p++;
        int left = 0, zero = 0, width = 0, prec = -1;
        for (;;) {
            if (*p == '-') left = 1;
            else if (*p == '0') zero = 1;
            else break;
            p++;
        }
        while (*p >= '0' && *p <= '9') { width = width * 10 + (*p - '0'); p++; }
        if (*p == '.') { p++; prec = 0; while (*p >= '0' && *p <= '9') { prec = prec * 10 + (*p - '0'); p++; } }
        switch (*p) {
        case 'c': {
            char buf[1]; buf[0] = (char)va_arg(ap, int);
            if (left) { write(fd, buf, 1); put_pad_fd(fd, width - 1, ' '); }
            else { put_pad_fd(fd, width - 1, ' '); write(fd, buf, 1); }
            break;
        }
        case 's': {
            const char *s = va_arg(ap, const char *);
            if (!s) s = "(null)";
            int len = (int)strlen(s);
            if (prec >= 0 && prec < len) len = prec;
            if (left) { write(fd, s, len); put_pad_fd(fd, width - len, ' '); }
            else { put_pad_fd(fd, width - len, ' '); write(fd, s, len); }
            break;
        }
        case 'l': {
            p++;
            if (*p == 'l') {
                p++;
                unsigned long long v;
                int neg = 0;
                if (*p == 'd') { long long x = va_arg(ap, long long); if (x < 0) { neg = 1; v = (unsigned long long)(-x); } else v = (unsigned long long)x; }
                else if (*p == 'u') { v = va_arg(ap, unsigned long long); }
                else if (*p == 'x') { v = va_arg(ap, unsigned long long); }
                else if (*p == 'X') { v = va_arg(ap, unsigned long long); }
                else { put_char_fd(fd, '%'); put_char_fd(fd, 'l'); put_char_fd(fd, 'l'); put_char_fd(fd, *p); break; }
                char tmp[32]; int i = 0; const char *digits = (*p == 'X') ? "0123456789ABCDEF" : (*p == 'x') ? "0123456789abcdef" : "0123456789";
                if (v == 0) tmp[i++] = '0'; else while (v > 0) { tmp[i++] = digits[v % 10]; v /= 10; }
                int len = i + (neg ? 1 : 0);
                if (left) { if (neg) put_char_fd(fd, '-'); for (int k = i - 1; k >= 0; k--) put_char_fd(fd, tmp[k]); put_pad_fd(fd, width - len, ' '); }
                else { put_pad_fd(fd, width - len, (zero && prec < 0) ? '0' : ' '); if (neg) put_char_fd(fd, '-'); for (int k = i - 1; k >= 0; k--) put_char_fd(fd, tmp[k]); }
                break;
            }
            unsigned long v;
            int neg = 0;
            if (*p == 'd') { long x = va_arg(ap, long); if (x < 0) { neg = 1; v = (unsigned long)(-x); } else v = (unsigned long)x; }
            else if (*p == 'u') { v = va_arg(ap, unsigned long); }
            else if (*p == 'x') { v = va_arg(ap, unsigned long); }
            else if (*p == 'X') { v = va_arg(ap, unsigned long); }
            else { put_char_fd(fd, '%'); put_char_fd(fd, 'l'); put_char_fd(fd, *p); break; }
            char tmp[32]; int i = 0; const char *digits = (*p == 'X') ? "0123456789ABCDEF" : (*p == 'x') ? "0123456789abcdef" : "0123456789";
            if (v == 0) tmp[i++] = '0'; else while (v > 0) { tmp[i++] = digits[v % 10]; v /= 10; }
            int len = i + (neg ? 1 : 0);
            if (left) { if (neg) put_char_fd(fd, '-'); for (int k = i - 1; k >= 0; k--) put_char_fd(fd, tmp[k]); put_pad_fd(fd, width - len, ' '); }
            else { put_pad_fd(fd, width - len, (zero && prec < 0) ? '0' : ' '); if (neg) put_char_fd(fd, '-'); for (int k = i - 1; k >= 0; k--) put_char_fd(fd, tmp[k]); }
            break;
        }
        case 'd': {
            int x = va_arg(ap, int);
            unsigned long long v; int neg = 0;
            if (x < 0) { neg = 1; v = (unsigned long long)(-x); } else v = (unsigned long long)x;
            char tmp[32]; int i = 0;
            if (v == 0) tmp[i++] = '0'; else while (v > 0) { tmp[i++] = '0' + v % 10; v /= 10; }
            int len = i + (neg ? 1 : 0);
            if (left) { if (neg) put_char_fd(fd, '-'); for (int k = i - 1; k >= 0; k--) put_char_fd(fd, tmp[k]); put_pad_fd(fd, width - len, ' '); }
            else { put_pad_fd(fd, width - len, (zero && prec < 0) ? '0' : ' '); if (neg) put_char_fd(fd, '-'); for (int k = i - 1; k >= 0; k--) put_char_fd(fd, tmp[k]); }
            break;
        }
        case 'u': {
            unsigned long long v = va_arg(ap, unsigned int);
            char tmp[32]; int i = 0;
            if (v == 0) tmp[i++] = '0'; else while (v > 0) { tmp[i++] = '0' + v % 10; v /= 10; }
            int len = i;
            if (left) { for (int k = i - 1; k >= 0; k--) put_char_fd(fd, tmp[k]); put_pad_fd(fd, width - len, ' '); }
            else { put_pad_fd(fd, width - len, (zero && prec < 0) ? '0' : ' '); for (int k = i - 1; k >= 0; k--) put_char_fd(fd, tmp[k]); }
            break;
        }
        case 'x': {
            unsigned long long v = va_arg(ap, unsigned int);
            char tmp[32]; int i = 0;
            if (v == 0) tmp[i++] = '0'; else while (v > 0) { tmp[i++] = "0123456789abcdef"[v % 16]; v /= 16; }
            int len = i;
            if (left) { for (int k = i - 1; k >= 0; k--) put_char_fd(fd, tmp[k]); put_pad_fd(fd, width - len, ' '); }
            else { put_pad_fd(fd, width - len, (zero && prec < 0) ? '0' : ' '); for (int k = i - 1; k >= 0; k--) put_char_fd(fd, tmp[k]); }
            break;
        }
        case 'X': {
            unsigned long long v = va_arg(ap, unsigned int);
            char tmp[32]; int i = 0;
            if (v == 0) tmp[i++] = '0'; else while (v > 0) { tmp[i++] = "0123456789ABCDEF"[v % 16]; v /= 16; }
            int len = i;
            if (left) { for (int k = i - 1; k >= 0; k--) put_char_fd(fd, tmp[k]); put_pad_fd(fd, width - len, ' '); }
            else { put_pad_fd(fd, width - len, (zero && prec < 0) ? '0' : ' '); for (int k = i - 1; k >= 0; k--) put_char_fd(fd, tmp[k]); }
            break;
        }
        case 'p': {
            unsigned long long v = (unsigned long long)(unsigned long)va_arg(ap, void *);
            char tmp[32]; int i = 0;
            if (v == 0) { write(fd, "(nil)", 5); break; }
            tmp[i++] = '0'; tmp[i++] = 'x';
            int s = i; while (v > 0) { tmp[i++] = "0123456789abcdef"[v % 16]; v /= 16; }
            int len = i;
            if (left) { for (int k = s; k < i; k++) put_char_fd(fd, tmp[k]); put_pad_fd(fd, width - len, ' '); }
            else { put_pad_fd(fd, width - len, ' '); for (int k = s; k < i; k++) put_char_fd(fd, tmp[k]); }
            break;
        }
        case 'z': {
            p++;
            if (*p == 'u') {
                size_t v = va_arg(ap, size_t);
                char tmp[32]; int i = 0;
                if (v == 0) { put_char_fd(fd, '0'); }
                else { while (v > 0) { tmp[i++] = '0' + v % 10; v /= 10; } while (i > 0) put_char_fd(fd, tmp[--i]); }
            } else if (*p == 'x') {
                size_t v = va_arg(ap, size_t);
                put_char_fd(fd, '0'); put_char_fd(fd, 'x');
                char tmp[32]; int i = 0;
                if (v == 0) { put_char_fd(fd, '0'); }
                else { while (v > 0) { tmp[i++] = '0' + v % 16; v /= 16; } while (i > 0) put_char_fd(fd, tmp[--i]); }
            } else {
                put_char_fd(fd, '%'); put_char_fd(fd, 'z'); put_char_fd(fd, *p);
            }
            break;
        }
        case 'f':
        case 'F': {
            double v = va_arg(ap, double);
            if (v < 0) { put_char_fd(fd, '-'); v = -v; }
            long long ip = (long long)v;
            double frac = v - (double)ip;
            if (frac < 0) frac = -frac;
            if (ip == 0) { put_char_fd(fd, '0'); }
            else {
                char tmp[32]; int i = 0;
                unsigned long long u = (unsigned long long)ip;
                while (u > 0) { tmp[i++] = '0' + u % 10; u /= 10; }
                while (i > 0) put_char_fd(fd, tmp[--i]);
            }
            put_char_fd(fd, '.');
            for (int k = 0; k < 6; k++) {
                frac *= 10.0;
                put_char_fd(fd, '0' + (int)frac);
                frac -= (int)frac;
            }
            break;
        }
        case 'e': {
            double v = va_arg(ap, double);
            if (v < 0) { put_char_fd(fd, '-'); v = -v; }
            if (v == 0.0) { write(fd, "0.000000e+00", 13); break; }
            int exp = 0;
            while (v >= 10.0) { v /= 10.0; exp++; }
            while (v < 1.0) { v *= 10.0; exp--; }
            long long ip = (long long)v;
            double frac = v - (double)ip;
            if (ip == 0) put_char_fd(fd, '0');
            else {
                char tmp[4]; int i = 0;
                while (ip > 0) { tmp[i++] = '0' + ip % 10; ip /= 10; }
                while (i > 0) put_char_fd(fd, tmp[--i]);
            }
            put_char_fd(fd, '.');
            for (int k = 0; k < 6; k++) {
                frac *= 10.0;
                put_char_fd(fd, '0' + (int)frac);
                frac -= (int)frac;
            }
            put_char_fd(fd, 'e');
            if (exp >= 0) put_char_fd(fd, '+');
            else { put_char_fd(fd, '-'); exp = -exp; }
            if (exp < 10) put_char_fd(fd, '0');
            char tmp[4]; int i = 0;
            while (exp > 0) { tmp[i++] = '0' + exp % 10; exp /= 10; }
            while (i > 0) put_char_fd(fd, tmp[--i]);
            break;
        }
        case 'g': {
            double v = va_arg(ap, double);
            int exp = 0;
            double av = v < 0 ? -v : v;
            if (av == 0.0) { write(fd, "0", 1); break; }
            while (av >= 10.0) { av /= 10.0; exp++; }
            while (av < 1.0) { av *= 10.0; exp--; }
            if (exp >= -4 && exp < 6) {
                if (v < 0) put_char_fd(fd, '-');
                double x = v < 0 ? -v : v;
                long long ip = (long long)x;
                double frac = x - (double)ip;
                if (ip == 0) put_char_fd(fd, '0');
                else {
                    char tmp[32]; int i = 0;
                    while (ip > 0) { tmp[i++] = '0' + ip % 10; ip /= 10; }
                    while (i > 0) put_char_fd(fd, tmp[--i]);
                }
                int prec = 6 - exp - 1;
                if (prec > 0) {
                    put_char_fd(fd, '.');
                    for (int k = 0; k < prec; k++) {
                        frac *= 10.0;
                        put_char_fd(fd, '0' + (int)frac);
                        frac -= (int)frac;
                    }
                }
            } else {
                if (v < 0) put_char_fd(fd, '-');
                double x = v < 0 ? -v : v;
                while (x >= 10.0) { x /= 10.0; exp++; }
                while (x < 1.0) { x *= 10.0; exp--; }
                long long ip = (long long)x;
                double frac = x - (double)ip;
                if (ip == 0) put_char_fd(fd, '0');
                else {
                    char tmp[4]; int i = 0;
                    while (ip > 0) { tmp[i++] = '0' + ip % 10; ip /= 10; }
                    while (i > 0) put_char_fd(fd, tmp[--i]);
                }
                put_char_fd(fd, '.');
                for (int k = 0; k < 5; k++) {
                    frac *= 10.0;
                    put_char_fd(fd, '0' + (int)frac);
                    frac -= (int)frac;
                }
                put_char_fd(fd, 'e');
                if (exp >= 0) put_char_fd(fd, '+');
                else { put_char_fd(fd, '-'); exp = -exp; }
                if (exp < 10) put_char_fd(fd, '0');
                char tmp[4]; int i = 0;
                while (exp > 0) { tmp[i++] = '0' + exp % 10; exp /= 10; }
                while (i > 0) put_char_fd(fd, tmp[--i]);
            }
            break;
        }
        case '%': { put_char_fd(fd, '%'); break; }
        default: { put_char_fd(fd, '%'); put_char_fd(fd, *p); break; }
        }
    }
}

int printf(const char *fmt, ...) { va_list ap; va_start(ap, fmt); format_fd(1, fmt, ap); va_end(ap); return 0; }
int vprintf(const char *fmt, va_list ap) { format_fd(1, fmt, ap); return 0; }
int fprintf(FILE *s, const char *fmt, ...) { va_list ap; va_start(ap, fmt); format_fd(s->fd, fmt, ap); va_end(ap); return 0; }
int vfprintf(FILE *s, const char *fmt, va_list ap) { format_fd(s->fd, fmt, ap); return 0; }

int puts(const char *s) { write(1, s, strlen(s)); write(1, "\n", 1); return 0; }
int fputs(const char *s, FILE *stream) { write(stream->fd, s, strlen(s)); return 0; }
int fputc(int c, FILE *s) { char ch = (char)c; write(s->fd, &ch, 1); return 0; }
int putc(int c, FILE *s) { return fputc(c, s); }
int putchar(int c) { return fputc(c, stdout); }

int getc(FILE *stream)
{
    if (stream->has_pushback) { stream->has_pushback = 0; return stream->pushback; }
    unsigned char c;
    long n = read(stream->fd, &c, 1);
    if (n <= 0) { stream->eof = 1; return EOF; }
    return c;
}

int getchar(void) { return getc(stdin); }

int ungetc(int c, FILE *stream)
{
    if (c == EOF) return EOF;
    stream->pushback = c;
    stream->has_pushback = 1;
    stream->eof = 0;
    return c;
}

char *fgets(char *s, int n, FILE *stream)
{
    int i = 0;
    while (i < n - 1) {
        int c = getc(stream);
        if (c == EOF) { if (i == 0) return NULL; break; }
        s[i++] = (char)c;
        if (c == '\n') break;
    }
    s[i] = '\0';
    return i > 0 ? s : NULL;
}

size_t fread(void *ptr, size_t size, size_t n, FILE *stream)
{
    size_t total = size * n;
    long got = read(stream->fd, ptr, total);
    if (got < 0) { stream->error = 1; return 0; }
    if (got < (long)total) stream->eof = 1;
    return (size_t)got / size;
}

size_t fwrite(const void *ptr, size_t size, size_t n, FILE *stream)
{
    size_t total = size * n;
    long wrote = write(stream->fd, ptr, total);
    if (wrote < (long)total) { stream->error = 1; return 0; }
    return n;
}

int feof(FILE *stream) { return stream->eof; }
int ferror(FILE *stream) { return stream->error; }
void clearerr(FILE *stream) { stream->eof = 0; stream->error = 0; }
int fflush(FILE *stream) { (void)stream; return 0; }

typedef struct { char *data; size_t len; size_t cap; } sbuf_t;

static void sbuf_init(sbuf_t *b)
{
    b->data = sbrk(0);
    b->cap = 64;
    b->len = 0;
    sbrk(b->cap);
}

static void sbuf_grow(sbuf_t *b, size_t needed)
{
    while (b->len + needed > b->cap) {
        b->cap *= 2;
        sbrk(b->cap - (b->cap / 2));
    }
}

static void sbuf_putc(sbuf_t *b, char c) { sbuf_grow(b, 1); b->data[b->len++] = c; }
static void sbuf_puts(sbuf_t *b, const char *s) { size_t l = strlen(s); sbuf_grow(b, l); memcpy(b->data + b->len, s, l); b->len += l; }
static void sbuf_format(sbuf_t *b, const char *fmt, va_list ap)
{
    for (const char *p = fmt; *p; p++) {
        if (*p != '%') { sbuf_putc(b, *p); continue; }
        p++;
        switch (*p) {
        case 'c': { sbuf_putc(b, (char)va_arg(ap, int)); break; }
        case 's': { const char *s = va_arg(ap, const char *); if (s) sbuf_puts(b, s); else sbuf_puts(b, "(null)"); break; }
        case 'd': { char tmp[32]; int v = va_arg(ap, int); int i = 0; unsigned int u; if (v < 0) { sbuf_putc(b, '-'); u = 0 - (unsigned int)v; } else { u = (unsigned int)v; } if (u == 0) { sbuf_putc(b, '0'); } else { while (u > 0) { tmp[i++] = '0' + u % 10; u /= 10; } while (i > 0) sbuf_putc(b, tmp[--i]); } break; }
        case 'u': { char tmp[32]; unsigned int v = va_arg(ap, unsigned int); int i = 0; if (v == 0) { sbuf_putc(b, '0'); } else { while (v > 0) { tmp[i++] = '0' + v % 10; v /= 10; } while (i > 0) sbuf_putc(b, tmp[--i]); } break; }
        case 'x': { char tmp[32]; unsigned int v = va_arg(ap, unsigned int); int i = 0; if (v == 0) { sbuf_putc(b, '0'); } else { while (v > 0) { tmp[i++] = '0' + v % 16; v /= 16; } sbuf_putc(b, '0'); sbuf_putc(b, 'x'); while (i > 0) sbuf_putc(b, tmp[--i]); } break; }
        case 'X': { char tmp[32]; unsigned int v = va_arg(ap, unsigned int); int i = 0; if (v == 0) { sbuf_putc(b, '0'); } else { while (v > 0) { tmp[i++] = '0' + v % 16; v /= 16; } sbuf_putc(b, '0'); sbuf_putc(b, 'x'); while (i > 0) sbuf_putc(b, tmp[--i]); } break; }
        case 'p': { char tmp[32]; void *vp = va_arg(ap, void *); int i = 0; sbuf_putc(b, '0'); sbuf_putc(b, 'x'); unsigned long val = (unsigned long)vp; if (val == 0) { sbuf_putc(b, '0'); } else { while (val > 0) { tmp[i++] = '0' + val % 16; val /= 16; } while (i > 0) sbuf_putc(b, tmp[--i]); } break; }
        case 'z': {
            p++;
            if (*p == 'u') {
                size_t v = va_arg(ap, size_t);
                char tmp[32]; int i = 0;
                if (v == 0) { sbuf_putc(b, '0'); }
                else { while (v > 0) { tmp[i++] = '0' + v % 10; v /= 10; } while (i > 0) sbuf_putc(b, tmp[--i]); }
            } else if (*p == 'x') {
                size_t v = va_arg(ap, size_t);
                sbuf_putc(b, '0'); sbuf_putc(b, 'x');
                char tmp[32]; int i = 0;
                if (v == 0) { sbuf_putc(b, '0'); }
                else { while (v > 0) { tmp[i++] = '0' + v % 16; v /= 16; } while (i > 0) sbuf_putc(b, tmp[--i]); }
            } else {
                sbuf_putc(b, '%'); sbuf_putc(b, 'z'); sbuf_putc(b, *p);
            }
            break;
        }
        case '%': { sbuf_putc(b, '%'); break; }
        default: { sbuf_putc(b, '%'); sbuf_putc(b, *p); break; }
        }
    }
}

int sprintf(char *str, const char *fmt, ...)
{
    va_list ap; va_start(ap, fmt);
    sbuf_t b; sbuf_init(&b);
    sbuf_format(&b, fmt, ap);
    va_end(ap);
    size_t to_copy = b.len < 63 ? b.len : 63;
    if (to_copy > 0) memcpy(str, b.data, to_copy);
    str[to_copy] = '\0';
    return (int)b.len;
}

int snprintf(char *str, size_t n, const char *fmt, ...)
{
    va_list ap; va_start(ap, fmt);
    sbuf_t b; sbuf_init(&b);
    sbuf_format(&b, fmt, ap);
    va_end(ap);
    size_t to_copy = b.len < n - 1 ? b.len : n - 1;
    if (to_copy > 0) memcpy(str, b.data, to_copy);
    str[to_copy] = '\0';
    return (int)b.len;
}

int vsprintf(char *str, const char *fmt, va_list ap)
{
    sbuf_t b; sbuf_init(&b);
    sbuf_format(&b, fmt, ap);
    if (b.len > 0) memcpy(str, b.data, b.len);
    str[b.len] = '\0';
    return (int)b.len;
}

int vsnprintf(char *str, size_t n, const char *fmt, va_list ap)
{
    sbuf_t b; sbuf_init(&b);
    sbuf_format(&b, fmt, ap);
    size_t to_copy = b.len < n - 1 ? b.len : n - 1;
    if (to_copy > 0) memcpy(str, b.data, to_copy);
    str[to_copy] = '\0';
    return (int)b.len;
}

void perror(const char *s)
{
    if (s) { write(2, s, strlen(s)); write(2, ": ", 2); }
    char buf[64];
    unsigned long e = (unsigned long)errno;
    int start = 63;
    buf[start] = '\0';
    if (e == 0) { buf[--start] = '0'; }
    else { while (e > 0) { buf[--start] = '0' + (e % 10); e /= 10; } }
    write(2, buf + start, 63 - start);
    write(2, "\n", 1);
}

int fgetc(FILE *stream)
{
    int c = getc(stream);
    if (c == EOF) return EOF;
    return c;
}

int ftell(FILE *stream)
{
    return (int)lseek(stream->fd, 0, SEEK_CUR);
}

int fseek(FILE *stream, long offset, int whence)
{
    return (int)lseek(stream->fd, offset, whence);
}

void rewind(FILE *stream)
{
    lseek(stream->fd, 0, SEEK_SET);
    stream->eof = 0;
    stream->error = 0;
}

void setbuf(FILE *stream, char *buf)
{
    (void)stream;
    (void)buf;
}

int setvbuf(FILE *stream, char *buf, int mode, size_t size)
{
    (void)stream;
    (void)buf;
    (void)mode;
    (void)size;
    return 0;
}

int remove(const char *path)
{
    return (int)syscall(SYS_unlink, path);
}

int rename(const char *old, const char *new)
{
    return (int)syscall(SYS_rename, old, new);
}

static int _scan_skip_ws(const char **p)
{
    int n = 0;
    while (**p == ' ' || **p == '\t' || **p == '\n' || **p == '\r' || **p == '\v' || **p == '\f') {
        (*p)++;
        n++;
    }
    return n;
}

static int _scan_int(const char **p, int base, long *out)
{
    int sign = 1;
    if (**p == '-') { sign = -1; (*p)++; }
    else if (**p == '+') { (*p)++; }
    if (base == 0) {
        if (**p == '0' && ((*p)[1] == 'x' || (*p)[1] == 'X')) { base = 16; (*p) += 2; }
        else if (**p == '0') base = 8;
        else base = 10;
    }
    long val = 0;
    int found = 0;
    while (1) {
        int d;
        char c = **p;
        if (c >= '0' && c <= '9') d = c - '0';
        else if (c >= 'a' && c <= 'z') d = c - 'a' + 10;
        else if (c >= 'A' && c <= 'Z') d = c - 'A' + 10;
        else break;
        if (d >= base) break;
        val = val * base + d;
        (*p)++;
        found = 1;
    }
    if (!found) return 0;
    *out = sign * val;
    return 1;
}

int vsscanf(const char *str, const char *fmt, va_list ap)
{
    int assigned = 0;
    const char *p = str;
    for (const char *f = fmt; *f; f++) {
        if (*f == ' ') continue;
        if (*f != '%') {
            _scan_skip_ws(&p);
            if (*p != *f) return assigned;
            p++;
            continue;
        }
        f++;
        switch (*f) {
        case 'd': {
            _scan_skip_ws(&p);
            long v;
            if (_scan_int(&p, 10, &v)) {
                *va_arg(ap, int *) = (int)v;
                assigned++;
            } else return assigned;
            break;
        }
        case 'u': {
            _scan_skip_ws(&p);
            long v;
            if (_scan_int(&p, 10, &v)) {
                *va_arg(ap, unsigned int *) = (unsigned int)v;
                assigned++;
            } else return assigned;
            break;
        }
        case 'x': {
            _scan_skip_ws(&p);
            long v;
            if (_scan_int(&p, 16, &v)) {
                *va_arg(ap, unsigned int *) = (unsigned int)v;
                assigned++;
            } else return assigned;
            break;
        }
        case 's': {
            _scan_skip_ws(&p);
            char *dst = va_arg(ap, char *);
            int i = 0;
            while (*p && *p != ' ' && *p != '\t' && *p != '\n' && *p != '\r')
                dst[i++] = *p++;
            dst[i] = '\0';
            if (i > 0) assigned++;
            else return assigned;
            break;
        }
        case 'c': {
            _scan_skip_ws(&p);
            *va_arg(ap, char *) = *p++;
            assigned++;
            break;
        }
        case 'f': {
            _scan_skip_ws(&p);
            int sign = 1;
            if (*p == '-') { sign = -1; p++; }
            else if (*p == '+') { p++; }
            double val = 0.0;
            while (*p >= '0' && *p <= '9') { val = val * 10.0 + (*p - '0'); p++; }
            if (*p == '.') {
                p++;
                double frac = 1.0;
                while (*p >= '0' && *p <= '9') { frac /= 10.0; val += (*p - '0') * frac; p++; }
            }
            *va_arg(ap, double *) = sign * val;
            assigned++;
            break;
        }
        case '%':
            _scan_skip_ws(&p);
            if (*p != '%') return assigned;
            p++;
            break;
        default:
            return assigned;
        }
    }
    return assigned;
}

int sscanf(const char *str, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int n = vsscanf(str, fmt, ap);
    va_end(ap);
    return n;
}

int fscanf(FILE *stream, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    char buf[1024];
    int i = 0;
    int c;
    while (i < 1023 && (c = getc(stream)) != EOF && c != '\n')
        buf[i++] = (char)c;
    buf[i] = '\0';
    int n = vsscanf(buf, fmt, ap);
    va_end(ap);
    return n;
}

int vfscanf(FILE *stream, const char *fmt, va_list ap)
{
    char buf[1024];
    int i = 0;
    int c;
    while (i < 1023 && (c = getc(stream)) != EOF && c != '\n')
        buf[i++] = (char)c;
    buf[i] = '\0';
    return vsscanf(buf, fmt, ap);
}

int fileno(FILE *stream)
{
    return stream->fd;
}

FILE *fdopen(int fd, const char *mode)
{
    (void)mode;
    static FILE _fdopen_file;
    _fdopen_file.fd = fd;
    _fdopen_file.mode = 0;
    _fdopen_file.eof = 0;
    _fdopen_file.error = 0;
    _fdopen_file.has_pushback = 0;
    _fdopen_file.pushback = 0;
    return &_fdopen_file;
}
