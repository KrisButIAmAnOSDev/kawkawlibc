#include "fenv.h"

int feclearexcept(int excepts)
{
    (void)excepts;
    return 0;
}

int feraiseexcept(int excepts)
{
    (void)excepts;
    return 0;
}

int fgetexceptflag(fenv_t *flagp, int excepts)
{
    (void)flagp;
    (void)excepts;
    return 0;
}

int fsetexceptflag(const fenv_t *flagp, int excepts)
{
    (void)flagp;
    (void)excepts;
    return 0;
}

int fegetroundmode(void)
{
    return FE_TONEAREST;
}

int fesetroundmode(int rounding_mode)
{
    (void)rounding_mode;
    return 0;
}

int fegetenv(fenv_t *envp)
{
    (void)envp;
    return 0;
}

int fesetenv(const fenv_t *envp)
{
    (void)envp;
    return 0;
}