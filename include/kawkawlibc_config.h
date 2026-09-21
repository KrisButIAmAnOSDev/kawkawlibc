#ifndef KAWKAWLIBC_CONFIG_H
#define KAWKAWLIBC_CONFIG_H

/* Kawkawlibc configuration.
   Each macro defaults to 1 (enabled).
   Override with -DENABLE_XXX=0 to disable, or -DENABLE_XXX=1 to enable. */

#ifndef ENABLE_SYSCALL_READ
#define ENABLE_SYSCALL_READ   1
#endif
#ifndef ENABLE_SYSCALL_WRITE
#define ENABLE_SYSCALL_WRITE  1
#endif
#ifndef ENABLE_SYSCALL_OPEN
#define ENABLE_SYSCALL_OPEN   1
#endif
#ifndef ENABLE_SYSCALL_CLOSE
#define ENABLE_SYSCALL_CLOSE  1
#endif
#ifndef ENABLE_SYSCALL_LSEEK
#define ENABLE_SYSCALL_LSEEK  1
#endif
#ifndef ENABLE_SYSCALL_GETCWD
#define ENABLE_SYSCALL_GETCWD 1
#endif
#ifndef ENABLE_SYSCALL_STAT
#define ENABLE_SYSCALL_STAT   1
#endif
#ifndef ENABLE_SYSCALL_EXIT
#define ENABLE_SYSCALL_EXIT   1
#endif
#ifndef ENABLE_SYSCALL_BRK
#define ENABLE_SYSCALL_BRK    1
#endif

#ifndef ENABLE_MALLOC
#define ENABLE_MALLOC 1
#endif

#ifndef ENABLE_STDLIB
#define ENABLE_STDLIB 1
#endif

#ifndef ENABLE_STRING
#define ENABLE_STRING 1
#endif

#ifndef ENABLE_CTYPE
#define ENABLE_CTYPE 1
#endif

#ifndef ENABLE_ASSERT
#define ENABLE_ASSERT 1
#endif

#ifndef ENABLE_STDIO
#define ENABLE_STDIO 1
#endif

#ifndef ENABLE_ERRNO
#define ENABLE_ERRNO 1
#endif

#ifndef ENABLE_EASTER
#define ENABLE_EASTER 1
#endif

#ifndef ENABLE_THREADS
#define ENABLE_THREADS 1
#endif

#ifndef ENABLE_WCHAR
#define ENABLE_WCHAR 1
#endif

#ifndef ENABLE_WCTYPE
#define ENABLE_WCTYPE 1
#endif

#ifndef ENABLE_LOCALE
#define ENABLE_LOCALE 1
#endif

#ifndef ENABLE_MATH
#define ENABLE_MATH 1
#endif

#ifndef ENABLE_SIGNAL
#define ENABLE_SIGNAL 1
#endif

#ifndef ENABLE_TIME
#define ENABLE_TIME 1
#endif

#ifndef ENABLE_FENV
#define ENABLE_FENV 1
#endif

#ifndef ENABLE_SETJMP
#define ENABLE_SETJMP 1
#endif

#ifndef ENABLE_UCHAR
#define ENABLE_UCHAR 1
#endif

#endif
