#ifndef KAWKAW_COMPLEX_H
#define KAWKAW_COMPLEX_H

#include "math.h"

#define complex _Complex
#define imag _Imaginary
#define I 1.0i

double complex cexp(double complex z);
double complex csin(double complex z);
double complex ccos(double complex z);
double complex ctan(double complex z);
double complex clog(double complex z);
double complex csqrt(double complex z);
double complex cpow(double complex x, double complex y);
double cabs(double complex z);
double complex conj(double complex z);
double creal(double complex z);
double cimag(double complex z);
double carg(double complex z);

float complex cexpf(float complex z);
float complex csinf(float complex z);
float complex ccosf(float complex z);
float complex ctanf(float complex z);
float complex clogf(float complex z);
float complex csqrtf(float complex z);
float complex cpowf(float complex x, float complex y);
float cabsf(float complex z);
float complex conjf(float complex z);
float crealf(float complex z);
float cimagf(float complex z);
float cargf(float complex z);

long double complex cexpl(long double complex z);
long double complex csinl(long double complex z);
long double complex ccosl(long double complex z);
long double complex ctanl(long double complex z);
long double complex clogl(long double complex z);
long double complex csqrtl(long double complex z);
long double complex cpowl(long double complex x, long double complex y);
long double cabsl(long double complex z);
long double complex conjl(long double complex z);
long double creall(long double complex z);
long double cimagl(long double complex z);
long double cargl(long double complex z);

#endif