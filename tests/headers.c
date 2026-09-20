#include <kawkawlibc.h>
#include <string.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdnoreturn.h>

struct point { char x; int y; };

noreturn void die(void)
{
    exit(1);
}

int sum(int count, ...)
{
    va_list ap;
    va_start(ap, count);
    int total = 0;
    for (int i = 0; i < count; i++)
        total += va_arg(ap, int);
    va_end(ap);
    return total;
}

int main(void)
{
    bool flag = true;
    size_t len = strlen("test");
    size_t off = offsetof(struct point, y);

    if (flag) {
        const char *m1 = "bool ok\n";
        write(1, m1, strlen(m1));
    }

    if (len == 4) {
        const char *m2 = "size_t ok\n";
        write(1, m2, strlen(m2));
    }

    if (off == 4) {
        const char *m3 = "offsetof ok\n";
        write(1, m3, strlen(m3));
    }

    if (sum(3, 10, 20, 30) == 60) {
        const char *m4 = "va_list ok\n";
        write(1, m4, strlen(m4));
    }

    return 0;
}
