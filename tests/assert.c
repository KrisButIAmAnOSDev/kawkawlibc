#include "assert.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int main(void)
{
    int passed = 0;
    assert(1);
    assert(1225 > 64);
    assert(1 != 0);
    passed++;

    char *msg = "assert works";
    assert(msg != NULL);
    assert(strcmp(msg, "assert works") == 0);
    passed++;

    assert(1225 == 1225);
    assert(64 < 69);
    passed++;

    printf("assert: %d tests passed (no failures)\n", passed);
    return 0;
}
