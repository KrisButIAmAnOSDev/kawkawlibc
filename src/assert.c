#include "assert.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

noreturn void assert_fail(const char *assertion, const char *file, int line, const char *func)
{
    fprintf(stderr, "assertion failed: %s\nfile: %s\nline: %d\nfunc: %s\n", assertion, file, line, func);
    exit(1);
}
