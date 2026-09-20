#include "stdlib.h"
#include "string.h"
#include "stdio.h"

int main(void) {
    int *a = malloc(10 * sizeof(int));
    if (!a) { printf("malloc failed\n"); return 1; }
    for (int i = 0; i < 10; i++) a[i] = i * 10;
    printf("malloc works: a[5]=%d\n", a[5]);

    int *b = calloc(5, sizeof(int));
    if (!b) { printf("calloc failed\n"); return 1; }
    int calloc_ok = 1;
    for (int i = 0; i < 5; i++) {
        if (b[i] != 0) { calloc_ok = 0; break; }
    }
    printf("calloc works: %s\n", calloc_ok ? "all zero" : "FAIL");

    int *c = malloc(3 * sizeof(int));
    if (!c) { printf("realloc alloc failed\n"); return 1; }
    for (int i = 0; i < 3; i++) c[i] = i;
    c = realloc(c, 6 * sizeof(int));
    if (!c) { printf("realloc failed\n"); return 1; }
    for (int i = 3; i < 6; i++) c[i] = i;
    printf("realloc works: c[4]=%d\n", c[4]);

    free(a);
    free(b);
    free(c);
    printf("free works\n");

    int *d = malloc(2 * sizeof(int));
    free(d);
    int *e = malloc(2 * sizeof(int));
    printf("reuse after free: %p == %p: %s\n", (void *)e, (void *)d, e == d ? "yes" : "no");

    int *big = malloc(10000 * sizeof(int));
    printf("big ptr: %p\n", (void *)big);
    if (big) {
        big[0] = 1225;
        printf("big[0]=1225 ok\n");
        big[100] = 1225;
        printf("big[100] ok\n");
        big[500] = 1225;
        printf("big[500] ok\n");
        big[1000] = 1225;
        printf("big[1000] ok\n");
        big[2500] = 1225;
        printf("big[2500] ok\n");
        big[9999] = 99;
        printf("big[9999]=%d ok\n", big[9999]);
        free(big);
    } else {
        printf("big alloc FAILED\n");
    }

    void *zero = malloc(0);
    printf("malloc(0) returns: %p\n", zero);

    return 0;
}
