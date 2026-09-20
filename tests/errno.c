#include "errno.h"
#include "stdio.h"
#include "kawkawlibc.h"

int main(void)
{
    errno = 1225;
    if (errno != 1225) {
        write(1, "errno write/read failed\n", 25);
        return 1;
    }

    errno = 0;
    if (errno != 0) {
        write(1, "errno reset failed\n", 20);
        return 1;
    }

    printf("errno: %ld\n", errno);
    printf("errno test passed\n");
    return 0;
}
