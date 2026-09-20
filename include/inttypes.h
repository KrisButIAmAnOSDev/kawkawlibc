#ifndef KAWKAW_INTTYPES_H
#define KAWKAW_INTTYPES_H

#include "stdint.h"

#define PRId8     "d"
#define PRId16    "d"
#define PRId32    "d"
#define PRId64    "lld"
#define PRIu8     "u"
#define PRIu16    "u"
#define PRIu32    "u"
#define PRIu64    "llu"
#define PRIx8     "x"
#define PRIx16    "x"
#define PRIx32    "x"
#define PRIx64    "llx"
#define PRIo8     "o"
#define PRIo16    "o"
#define PRIo32    "o"
#define PRIo64    "llo"
#define PRIX8     "X"
#define PRIX16    "X"
#define PRIX32    "X"
#define PRIX64    "llX"
#define PRIuMAX   "llu"
#define PRIdMAX   "lld"
#define PRIxMAX   "llx"

#define PRIuPTR   "lu"
#define PRIdPTR   "ld"
#define PRIxPTR   "lx"
#define PRIXPTR   "lX"

#define SCNd8     "d"
#define SCNu8     "u"
#define SCNd16    "d"
#define SCNu16    "u"
#define SCNd32    "d"
#define SCNu32    "u"
#define SCNd64    "lld"
#define SCNu64    "llu"

#define INT8_C(c)  c
#define UINT8_C(c) c ## U
#define INT16_C(c) c
#define UINT16_C(c) c ## U
#define INT32_C(c) c
#define UINT32_C(c) c ## U
#define INT64_C(c) c ## LL
#define UINT64_C(c) c ## ULL

#endif
