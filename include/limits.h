#ifndef KAWKAW_LIMITS_H
#define KAWKAW_LIMITS_H

#include "stdint.h"

/* Number of bits in a character (8 on all modern platforms) */
#define CHAR_BIT    8

/* char */
#define CHAR_MIN    (-128)
#define CHAR_MAX    127
#define SCHAR_MIN   (-128)
#define SCHAR_MAX   127
#define UCHAR_MAX   255

/* short */
#define SHRT_MIN    (-32768)
#define SHRT_MAX    32767
#define USHRT_MAX   65535

/* int */
#define INT_MIN     (-2147483647 - 1)
#define INT_MAX     2147483647
#define UINT_MAX    0xFFFFFFFFu

/* long */
#define LONG_MIN    (-9223372036854775807L - 1)
#define LONG_MAX    9223372036854775807L
#define ULONG_MAX   0xFFFFFFFFFFFFFFFFUL

/* long long */
#define LLONG_MIN   (-9223372036854775807LL - 1)
#define LLONG_MAX   9223372036854775807LL
#define ULLONG_MAX  0xFFFFFFFFFFFFFFFFULL

/* Multibyte */
#define MB_LEN_MAX  16

#endif