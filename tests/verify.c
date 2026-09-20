#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main(void)
{
    printf("Using OUR libc!\n");
    printf("sizeof(void*) = %zu\n", sizeof(void*));
    printf("write via printf: %s\n", "hello from kawkawlibc");

    char buf[256];
    sprintf(buf, "sprintf works: %d + %d = %d", 10, 20, 30);
    puts(buf);

    if (strcmp("abc", "abc") == 0) {
        puts("strcmp works");
    }

    void *p = (void *)0xDEADBEEF;
    printf("pointer: %p\n", p);

    return 0;
}
