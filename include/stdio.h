#ifndef KAWKAW_STDIO_H
#define KAWKAW_STDIO_H

#include "kawkawlibc.h"
#include "stdarg.h"
#include "stddef.h"

#define EOF (-1)

typedef struct {
    int fd;
    int mode;
    int eof;
    int error;
    int has_pushback;
    int pushback;
} FILE;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

int printf(const char *fmt, ...);
int vprintf(const char *fmt, va_list ap);
int fprintf(FILE *stream, const char *fmt, ...);
int vfprintf(FILE *stream, const char *fmt, va_list ap);
int sprintf(char *str, const char *fmt, ...);
int snprintf(char *str, size_t n, const char *fmt, ...);
int vsprintf(char *str, const char *fmt, va_list ap);
int vsnprintf(char *str, size_t n, const char *fmt, va_list ap);

int puts(const char *s);
int fputs(const char *s, FILE *stream);
int fputc(int c, FILE *stream);
int putc(int c, FILE *stream);
int putchar(int c);

int getc(FILE *stream);
int getchar(void);
int ungetc(int c, FILE *stream);

char *fgets(char *s, int n, FILE *stream);
size_t fread(void *ptr, size_t size, size_t n, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t n, FILE *stream);

int feof(FILE *stream);
int ferror(FILE *stream);
void clearerr(FILE *stream);
int fflush(FILE *stream);

void perror(const char *s);

#endif
