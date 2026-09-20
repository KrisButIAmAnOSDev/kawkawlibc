#ifndef KAWKAW_FLOAT_H
#define KAWKAW_FLOAT_H

/* Single precision (float) */
#define FLT_MANT_DIG    24
#define FLT_EPSILON     1.1920928955078125e-7f
#define FLT_DIG         6
#define FLT_DECIMAL_DIG 9
#define FLT_MIN         1.1754943508222875e-38f
#define FLT_MAX         3.4028234663852886e+38f
#define FLT_MIN_10_SUB  -37
#define FLT_MAX_10_SUB  38

/* Double precision (double) */
#define DBL_MANT_DIG    53
#define DBL_EPSILON     2.2204460492503131e-16
#define DBL_DIG         15
#define DBL_DECIMAL_DIG 17
#define DBL_MIN         2.2250738585072014e-308
#define DBL_MAX         1.7976931348623157e+308
#define DBL_MIN_10_SUB  -307
#define DBL_MAX_10_SUB  308

/* Long double (same as double on x86-64) */
#define LDBL_MANT_DIG    53
#define LDBL_EPSILON     2.2204460492503131e-16
#define LDBL_DIG         15
#define LDBL_DECIMAL_DIG 17
#define LDBL_MIN         2.2250738585072014e-308
#define LDBL_MAX         1.7976931348623157e+308
#define LDBL_MIN_10_SUB  -307
#define LDBL_MAX_10_SUB  308

#endif