#ifndef KAWKAW_FENV_H
#define KAWKAW_FENV_H

#include "stdint.h"

#define FE_TONEAREST  0
#define FE_UPWARD     0x10000
#define FE_DOWNWARD   0x20000
#define FE_TOWARDZERO 0x30000

#define FE_DIVBYZERO  0x02
#define FE_INEXACT    0x20
#define FE_INVALID    0x01
#define FE_OVERFLOW   0x04
#define FE_UNDERFLOW  0x08

#define FE_ALL_EXCEPT (FE_DIVBYZERO | FE_INEXACT | FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW)

typedef uint16_t fenv_t;

int feclearexcept(int excepts);
int feraiseexcept(int excepts);
int fgetexceptflag(fenv_t *flagp, int excepts);
int fsetexceptflag(const fenv_t *flagp, int excepts);
int fegetroundmode(void);
int fesetroundmode(int rounding_mode);
int fegetenv(fenv_t *envp);
int fesetenv(const fenv_t *envp);

#endif