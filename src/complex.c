#include "complex.h"

double cabs(double complex z) { return fabs(creal(z)) + fabs(cimag(z)); }
float cabsf(float complex z) { return fabsf(crealf(z)) + fabsf(cimagf(z)); }
long double cabsl(long double complex z) { return fabsl(creall(z)) + fabsl(cimagl(z)); }

double complex conj(double complex z) { return creal(z) - cimag(z) * I; }
float complex conjf(float complex z) { return crealf(z) - cimagf(z) * I; }
long double complex conjl(long double complex z) { return creall(z) - cimagl(z) * I; }

double creal(double complex z) { return z; }
float crealf(float complex z) { return z; }
long double creall(long double complex z) { return z; }

double cimag(double complex z) { return (z - creal(z)) / I; }
float cimagf(float complex z) { return (z - crealf(z)) / I; }
long double cimagl(long double complex z) { return (z - creall(z)) / I; }

double carg(double complex z) { return atan2(cimag(z), creal(z)); }
float cargf(float complex z) { return atan2f(cimagf(z), crealf(z)); }
long double cargl(long double complex z) { return atan2l(cimagl(z), creall(z)); }

double complex cexp(double complex z)
{
    double r = exp(creal(z));
    return r * cos(cimag(z)) + r * sin(cimag(z)) * I;
}
float complex cexpf(float complex z)
{
    float r = expf(crealf(z));
    return r * cosf(cimagf(z)) + r * sinf(cimagf(z)) * I;
}
long double complex cexpl(long double complex z)
{
    long double r = expl(creall(z));
    return r * cosl(cimagl(z)) + r * sinl(cimagl(z)) * I;
}

double complex csin(double complex z)
{
    double a = creal(z), b = cimag(z);
    return sin(a) * cosh(b) + cos(a) * sinh(b) * I;
}
float complex csinf(float complex z)
{
    float a = crealf(z), b = cimagf(z);
    return sinf(a) * coshf(b) + cosf(a) * sinhf(b) * I;
}
long double complex csinl(long double complex z)
{
    long double a = creall(z), b = cimagl(z);
    return sinl(a) * coshl(b) + cosl(a) * sinhl(b) * I;
}

double complex ccos(double complex z)
{
    double a = creal(z), b = cimag(z);
    return cos(a) * cosh(b) - sin(a) * sinh(b) * I;
}
float complex ccosf(float complex z)
{
    float a = crealf(z), b = cimagf(z);
    return cosf(a) * coshf(b) - sinf(a) * sinhf(b) * I;
}
long double complex ccosl(long double complex z)
{
    long double a = creall(z), b = cimagl(z);
    return cosl(a) * coshl(b) - sinl(a) * sinhl(b) * I;
}

double complex ctan(double complex z)
{
    return csin(z) / ccos(z);
}
float complex ctanf(float complex z)
{
    return csinf(z) / ccosf(z);
}
long double complex ctanl(long double complex z)
{
    return csinl(z) / ccosl(z);
}

double complex clog(double complex z)
{
    return log(cabs(z)) + carg(z) * I;
}
float complex clogf(float complex z)
{
    return logf(cabsf(z)) + cargf(z) * I;
}
long double complex clogl(long double complex z)
{
    return logl(cabsl(z)) + cargl(z) * I;
}

double complex csqrt(double complex z)
{
    double r = cabs(z);
    double theta = carg(z);
    return sqrt(r) * cos(theta / 2.0) + sqrt(r) * sin(theta / 2.0) * I;
}
float complex csqrtf(float complex z)
{
    float r = cabsf(z);
    float theta = cargf(z);
    return sqrtf(r) * cosf(theta / 2.0f) + sqrtf(r) * sinf(theta / 2.0f) * I;
}
long double complex csqrtl(long double complex z)
{
    long double r = cabsl(z);
    long double theta = cargl(z);
    return sqrtl(r) * cosl(theta / 2.0L) + sqrtl(r) * sinl(theta / 2.0L) * I;
}

double complex cpow(double complex x, double complex y)
{
    return cexp(y * clog(x));
}
float complex cpowf(float complex x, float complex y)
{
    return cexpf(y * clogf(x));
}
long double complex cpowl(long double complex x, long double complex y)
{
    return cexpl(y * clogl(x));
}