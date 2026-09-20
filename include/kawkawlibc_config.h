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

#endif
