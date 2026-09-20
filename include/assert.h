#ifndef KAWKAW_ASSERT_H
#define KAWKAW_ASSERT_H

#include "stdnoreturn.h"

noreturn void assert_fail(const char *assertion, const char *file, int line, const char *func);

#define assert(expr) \
    ((expr) ? (void)0 : assert_fail(#expr, __FILE__, __LINE__, __func__))

#define assert_perror(expr) \
    ((expr) ? (void)0 : (fprintf(stderr, "%s: %d: %s: %s\n", __FILE__, __LINE__, #expr, strerror(errno)), exit(1)))

#endif
