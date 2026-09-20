#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

int main(void)
{
    /* printf basics */
    printf("printf basic: %s\n", "hello");
    printf("percent: %%\n");
    printf("char: %c\n", 'A');
    printf("string: %s\n", "test");
    printf("int: %d\n", 42);
    printf("negative: %d\n", -17);
    printf("zero: %d\n", 0);
    printf("unsigned: %u\n", 12345u);
    printf("hex lower: %x\n", 255);
    printf("hex upper: %X\n", 255);
    printf("ptr: %p\n", (void *)0x1234);
    printf("null string: %s\n", (const char *)NULL);
    printf("multiple: %s %d %x\n", "args", 7, 0xabc);
    printf("max int: %d\n", 2147483647);
    printf("min int: %d\n", -2147483647 - 1);
    printf("unsigned max: %u\n", 0xFFFFFFFFu);

    /* sprintf */
    char buf[128];
    sprintf(buf, "sprintf: %d + %d = %d", 3, 4, 7);
    puts(buf);

    char buf2[64];
    snprintf(buf2, 10, "snpr: %010d", 42);
    puts(buf2);

    /* fprintf */
    fprintf(stderr, "stderr: %s %d\n", "to stderr", 99);

    /* puts/fputs/fputc/putchar */
    puts("puts works");
    fputs("fputs works", stderr);
    fputc('\n', stderr);
    putchar('A');
    putchar('\n');

    /* fgets */
    printf("fgets test: ");
    char line[128];
    if (fgets(line, sizeof(line), stdin)) {
        printf("got: %s", line);
    } else {
        printf("fgets got NULL (EOF or error)\n");
    }

    /* fread */
    printf("fread test: reading 1 byte from stdin\n");
    unsigned char byte;
    size_t read_items = fread(&byte, 1, 1, stdin);
    printf("fread returned %zu items\n", read_items);

    /* fwrite */
    fwrite("fwrite test\n", 1, 12, stdout);

    /* ungetc */
    printf("ungetc test\n");
    clearerr(stdin);
    int c = getchar();
    if (c != EOF) {
        printf("first char: %c\n", (char)c);
        ungetc(c, stdin);
        int c2 = getchar();
        printf("after ungetc: %c\n", (char)c2);
    }

    /* feof/ferror/clearerr */
    printf("eof=%d error=%d\n", feof(stdin), ferror(stdin));
    clearerr(stdin);
    printf("after clearerr: eof=%d error=%d\n", feof(stdin), ferror(stdin));

    /* perror */
    errno = 13;
    perror("perror test");

    printf("done\n");
    return 0;
}
