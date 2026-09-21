#include "setjmp.h"

int sigsetjmp(sigjmp_buf env, int savemask)
{
    (void)savemask;
    return setjmp(env);
}

void siglongjmp(sigjmp_buf env, int val)
{
    longjmp(env, val);
}