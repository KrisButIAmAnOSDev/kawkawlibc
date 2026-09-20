#ifndef KAWKAW_SYS_TYPES_H
#define KAWKAW_SYS_TYPES_H

#include "stddef.h"

typedef long ssize_t;
typedef long off_t;
typedef unsigned long size_t;
typedef long ptrdiff_t;

typedef int pid_t;
typedef int uid_t;
typedef int gid_t;
typedef int mode_t;
typedef long time_t;
typedef long clock_t;
typedef unsigned long useconds_t;
typedef long suseconds_t;
typedef unsigned long blksize_t;
typedef long blkcnt_t;
typedef long dev_t;
typedef long ino_t;
typedef long nlink_t;

typedef int wchar_t;

#define NULL ((void *)0)

#endif