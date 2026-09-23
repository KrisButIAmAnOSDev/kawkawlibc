#ifndef KAWKAW_MATH_H
#define KAWKAW_MATH_H

#include "stddef.h"

#define HUGE_VAL   1.0e300
#define HUGE_VALF  1.0e300f
#define HUGE_VALL  1.0e300L

#define INFINITY   1.0e300
#define NAN        0.0/0.0

#define FP_NAN     0
#define FP_INFINITE 1
#define FP_NORMAL  2
#define FP_SUBNORMAL 3
#define FP_ZERO    4

#define M_PI        3.14159265358979323846
#define M_PI_2      1.57079632679489661923
#define M_PI_4      0.78539816339744830962
#define M_1_PI      0.31830988618379067154
#define M_2_PI      0.63661977236758134308
#define M_E         2.71828182845904523536
#define M_LOG2E     1.44269504088896340736
#define M_LOG10E    0.43429448190325182765
#define M_LN2       0.69314718055994530942
#define M_LN10      2.30258509299404568402
#define M_SQRT2     1.41421356237309504880
#define M_SQRT1_2   0.70710678118654752440

double acos(double x);
double asin(double x);
double atan(double x);
double atan2(double y, double x);
double cos(double x);
double sin(double x);
double tan(double x);
double cosh(double x);
double sinh(double x);
double tanh(double x);
double exp(double x);
double log(double x);
double log10(double x);
double pow(double x, double y);
double sqrt(double x);
double ceil(double x);
double floor(double x);
double round(double x);
double trunc(double x);
double fabs(double x);
double fmin(double x, double y);
double fmax(double x, double y);
double fmod(double x, double y);
double ldexp(double x, int exp);
double frexp(double x, int *exp);
double modf(double x, double *iptr);
double hypot(double x, double y);
float modff(float x, float *iptr);
float hypotf(float x, float y);
long double modfl(long double x, long double *iptr);
long double hypotl(long double x, long double y);
float ldexpf(float x, int exp);
long double ldexpl(long double x, int exp);
double atan2(double y, double x);

float acosf(float x);
float asinf(float x);
float atanf(float x);
float atan2f(float y, float x);
float cosf(float x);
float sinf(float x);
float tanf(float x);
float coshf(float x);
float sinhf(float x);
float tanhf(float x);
float expf(float x);
float logf(float x);
float log10f(float x);
float powf(float x, float y);
float sqrtf(float x);
float ceilf(float x);
float floorf(float x);
float roundf(float x);
float truncf(float x);
float fabsf(float x);
float fminf(float x, float y);
float fmaxf(float x, float y);
float fmodf(float x, float y);

long double acosl(long double x);
long double asinl(long double x);
long double atanl(long double x);
long double atan2l(long double y, long double x);
long double cosl(long double x);
long double sinl(long double x);
long double tanl(long double x);
long double coshl(long double x);
long double sinhl(long double x);
long double tanhl(long double x);
long double expl(long double x);
long double logl(long double x);
long double log10l(long double x);
long double powl(long double x, long double y);
long double sqrtl(long double x);
long double ceill(long double x);
long double floorl(long double x);
long double roundl(long double x);
long double truncl(long double x);
long double fabsl(long double x);
long double fminl(long double x, long double y);
long double fmaxl(long double x, long double y);
long double fmodl(long double x, long double y);

int isnan(double x);
int isinf(double x);
int isfinite(double x);
int signbit(double x);

#endif