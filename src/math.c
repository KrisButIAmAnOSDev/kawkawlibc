#include "math.h"

double fabs(double x) { return x < 0 ? -x : x; }
float fabsf(float x) { return x < 0 ? -x : x; }
long double fabsl(long double x) { return x < 0 ? -x : x; }

double sqrt(double x)
{
    if (x <= 0) return 0;
    double guess = x;
    for (int i = 0; i < 32; i++) {
        if (guess == 0) break;
        guess = (guess + x / guess) / 2.0;
    }
    return guess;
}

float sqrtf(float x)
{
    if (x <= 0) return 0;
    float guess = x;
    for (int i = 0; i < 32; i++) {
        if (guess == 0) break;
        guess = (guess + x / guess) / 2.0f;
    }
    return guess;
}

long double sqrtl(long double x)
{
    if (x <= 0) return 0;
    long double guess = x;
    for (int i = 0; i < 32; i++) {
        if (guess == 0) break;
        guess = (guess + x / guess) / 2.0L;
    }
    return guess;
}

double ceil(double x)
{
    double t = (double)(long long)x;
    if (t < x) t += 1.0;
    return t;
}

float ceilf(float x)
{
    float t = (float)(long long)x;
    if (t < x) t += 1.0f;
    return t;
}

long double ceill(long double x)
{
    long double t = (long double)(long long)x;
    if (t < x) t += 1.0L;
    return t;
}

double floor(double x)
{
    double t = (double)(long long)x;
    if (t > x) t -= 1.0;
    return t;
}

float floorf(float x)
{
    float t = (float)(long long)x;
    if (t > x) t -= 1.0f;
    return t;
}

long double floorl(long double x)
{
    long double t = (long double)(long long)x;
    if (t > x) t -= 1.0L;
    return t;
}

double fmod(double x, double y)
{
    if (y == 0) return 0;
    double q = (double)(long long)(x / y);
    return x - q * y;
}

float fmodf(float x, float y)
{
    if (y == 0) return 0;
    float q = (float)(long long)(x / y);
    return x - q * y;
}

long double fmodl(long double x, long double y)
{
    if (y == 0) return 0;
    long double q = (long double)(long long)(x / y);
    return x - q * y;
}

double exp(double x)
{
    double result = 1.0;
    double term = 1.0;
    for (int i = 1; i < 20; i++) {
        term *= x / i;
        result += term;
    }
    return result;
}

double log(double x)
{
    if (x <= 0) return 0;
    double y = (x - 1) / (x + 1);
    double y2 = y * y;
    double result = 0.0;
    double term = y;
    for (int i = 1; i < 30; i += 2) {
        result += term / i;
        term *= y2;
    }
    return 2.0 * result;
}

double pow(double x, double y)
{
    if (y == 0) return 1.0;
    double result = 1.0;
    long long n = (long long)y;
    double base = x;
    if (n < 0) { base = 1.0 / x; n = -n; }
    while (n) {
        if (n & 1) result *= base;
        base *= base;
        n >>= 1;
    }
    return result;
}

double sin(double x)
{
    double result = 0.0;
    double term = x;
    for (int i = 1; i < 20; i += 2) {
        double sign = ((i / 2) % 2) ? -1.0 : 1.0;
        result += sign * term;
        term *= x * x / ((i + 1) * (i + 2));
    }
    return result;
}

double cos(double x)
{
    double result = 1.0;
    double term = 1.0;
    for (int i = 2; i < 22; i += 2) {
        term *= -x * x / (i * (i - 1));
        result += term;
    }
    return result;
}

double tan(double x) { return sin(x) / cos(x); }
double atan(double x)
{
    double sign = 1.0;
    if (x < 0) { sign = -1.0; x = -x; }
    double result = 0.0;
    double term = x;
    for (int i = 1; i < 30; i += 2) {
        double s = ((i / 2) % 2) ? -1.0 : 1.0;
        result += s * term / i;
        term *= x * x;
    }
    return sign * result;
}

double asin(double x)
{
    if (x <= -1.0) return -1.5707963267948966;
    if (x >= 1.0) return 1.5707963267948966;
    double result = 0.0;
    double term = x;
    for (int i = 1; i < 30; i += 2) {
        double s = ((i / 2) % 2) ? -1.0 : 1.0;
        result += s * term / i;
        term *= x * x * (i - 1) / (i + 1);
    }
    return result;
}

double acos(double x)
{
    return 1.5707963267948966 - asin(x);
}

double atan2(double y, double x)
{
    if (x == 0.0) return (y > 0) ? 1.5707963267948966 : -1.5707963267948966;
    return atan(y / x);
}

double frexp(double x, int *exp)
{
    if (x == 0.0) { *exp = 0; return 0.0; }
    int e = 0;
    double mant = x;
    while (mant >= 2.0) { mant /= 2.0; e++; }
    while (mant < 1.0) { mant *= 2.0; e--; }
    *exp = e;
    return mant;
}
double modf(double x, double *iptr) { *iptr = (double)(long long)x; return x - *iptr; }
double hypot(double x, double y) { return sqrt(x * x + y * y); }

int isnan(double x) { return x != x; }
int isinf(double x) { return x > 1e300 || x < -1e300; }
int isfinite(double x) { return !isnan(x) && !isinf(x); }
int signbit(double x) { return x < 0; }
