#include <kawkawlibc.h>
#include <stdint.h>
#include <string.h>

int main(void)
{
    char *p1 = sbrk(64);
    char *p2 = sbrk(64);

    if (p1 == (void *)-1 || p2 == (void *)-1) {
        write(1, "sbrk failed\n", 12);
        return 1;
    }

    memcpy(p1, "first heap block\n", 18);
    memcpy(p2, "second heap block\n", 19);
    write(1, p1, strlen("first heap block\n"));
    write(1, p2, strlen("second heap block\n"));

    char buf[64];
    memset(buf, 0, 64);
    const char *msg = "optimized memcpy/memset works\n";
    memcpy(buf, msg, strlen(msg));
    write(1, buf, strlen(msg));

    if (errno == 0) {
        write(1, "errno: 0 (no errors)\n", 22);
    } else {
        write(1, "errno: nonzero (errors!)\n", 26);
    }

    return 0;
}
