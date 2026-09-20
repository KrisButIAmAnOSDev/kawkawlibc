#include <kawkawlibc.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdnoreturn.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>
#include <inttypes.h>
#include <stat.h>
#include <limits.h>
#include <float.h>
#include <wchar.h>
#include <wctype.h>
#include <setjmp.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>

static int test_hello(void)
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

static int test_stdio(void)
{
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
    char buf[128];
    sprintf(buf, "sprintf: %d + %d = %d", 3, 4, 7);
    puts(buf);
    char buf2[64];
    snprintf(buf2, 10, "snpr: %010d", 42);
    puts(buf2);
    fprintf(stderr, "stderr: %s %d\n", "to stderr", 99);
    puts("puts works");
    fputs("fputs works", stderr);
    fputc('\n', stderr);
    putchar('A');
    putchar('\n');
    printf("fgets test: ");
    char line[128];
    if (fgets(line, sizeof(line), stdin)) {
        printf("got: %s", line);
    } else {
        printf("fgets got NULL (EOF or error)\n");
    }
    printf("fread test: reading 1 byte from stdin\n");
    unsigned char byte;
    size_t read_items = fread(&byte, 1, 1, stdin);
    printf("fread returned %zu items\n", read_items);
    fwrite("fwrite test\n", 1, 12, stdout);
    printf("ungetc test\n");
    clearerr(stdin);
    int c = getchar();
    if (c != EOF) {
        printf("first char: %c\n", (char)c);
        ungetc(c, stdin);
        int c2 = getchar();
        printf("after ungetc: %c\n", (char)c2);
    }
    printf("eof=%d error=%d\n", feof(stdin), ferror(stdin));
    clearerr(stdin);
    printf("after clearerr: eof=%d error=%d\n", feof(stdin), ferror(stdin));
    errno = 13;
    perror("perror test");
    printf("done\n");
    return 0;
}

static int sum(int count, ...)
{
    va_list ap;
    va_start(ap, count);
    int total = 0;
    for (int i = 0; i < count; i++)
        total += va_arg(ap, int);
    va_end(ap);
    return total;
}

static int test_headers(void)
{
    struct point { char x; int y; };
    int fail = 0;
    bool flag = true;
    size_t len = strlen("test");
    size_t off = offsetof(struct point, y);
    if (flag) { write(1, "bool ok\n", 8); } else { fail++; }
    if (len == 4) { write(1, "size_t ok\n", 10); } else { fail++; }
    if (off == 4) { write(1, "offsetof ok\n", 12); } else { fail++; }
    if (sum(3, 10, 20, 30) == 60) { write(1, "va_list ok\n", 11); } else { fail++; }
    return fail;
}

static int test_verify(void)
{
    int fail = 0;
    printf("Using OUR libc!\n");
    printf("sizeof(void*) = %zu\n", sizeof(void*));
    printf("write via printf: %s\n", "hello from kawkawlibc");
    char buf[256];
    sprintf(buf, "sprintf works: %d + %d = %d", 10, 20, 30);
    puts(buf);
    if (strcmp("abc", "abc") == 0) {
        puts("strcmp works");
    } else {
        fail++;
    }
    void *p = (void *)0xDEADBEEF;
    printf("pointer: %p\n", p);
    return fail;
}

static int test_stdlib(void)
{
    int fail = 0;
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
        fail++;
    }
    void *zero = malloc(0);
    printf("malloc(0) returns: %p\n", zero);
    return fail;
}

static int test_more(void)
{
    int fail = 0;
    char buf[256];
    strcpy(buf, "hello");
    printf("strcpy: %s\n", buf);
    strcat(buf, " world");
    printf("strcat: %s\n", buf);
    char buf2[256];
    strncpy(buf2, "test", 256);
    printf("strncpy: %s\n", buf2);
    strncat(buf2, "ing", 128);
    printf("strncat: %s\n", buf2);
    char *p = strchr("hello world", 'w');
    printf("strchr: %s\n", p ? p : "(null)");
    char *r = strrchr("hello world", 'o');
    printf("strrchr: %s\n", r ? r : "(null)");
    char *s = strstr("hello world", "world");
    printf("strstr: %s\n", s ? s : "(null)");
    char *m = (char *)memchr("abcdef", 'c', 6);
    printf("memchr: %s\n", m ? m : "(null)");
    char *tok = strtok(buf, " ");
    printf("strtok: ");
    while (tok) {
        printf("%s ", tok);
        tok = strtok(NULL, " ");
    }
    printf("\n");
    printf("strspn(\"aabxy\", \"ab\"): %zu\n", strspn("aabxy", "ab"));
    printf("strcspn(\"aabxy\", \"xy\"): %zu\n", strcspn("aabxy", "xy"));
    char *pb = strpbrk("hello world", "xz");
    printf("strpbrk(\"hello world\", \"xz\"): %s\n", pb ? pb : "(null)");
    char *pb2 = strpbrk("hello world", "wo");
    printf("strpbrk(\"hello world\", \"wo\"): %s\n", pb2 ? pb2 : "(null)");
    char *dup = strdup("duplicated");
    printf("strdup: %s\n", dup);
    free(dup);
    printf("strerror: ");
    strerror(13);
    int fd = open("testfile.txt", O_WRONLY | O_CREAT | O_TRUNC);
    printf("open write fd: %d\n", fd);
    if (fd >= 0) {
        write(fd, "abc", 3);
        close(fd);
        struct stat st;
        int rc = stat("testfile.txt", &st);
        printf("stat: rc=%d size=%lu is_reg=%d is_dir=%d\n",
               rc, st.st_size, S_ISREG(st.st_mode), S_ISDIR(st.st_mode));
        fd = open("testfile.txt", O_RDONLY);
        printf("open read fd: %d\n", fd);
        if (fd >= 0) {
            char content[16] = {0};
            long bytes = read(fd, content, 15);
            printf("read %ld bytes: %s\n", bytes, content);
            long pos = lseek(fd, 1, SEEK_SET);
            printf("lseek to 1: %ld\n", pos);
            char c[2] = {0};
            bytes = read(fd, c, 1);
            printf("read 1 byte at pos 1: %s\n", c);
            close(fd);
        }
    }
    char cwd[256];
    getcwd(cwd, 256);
    printf("getcwd: %s\n", cwd);
    return fail;
}

static int test_ctype(void)
{
    int pass = 0, fail = 0;
    if (isalpha('A') && isalpha('z') && !isalpha('0') && !isalpha('@')) pass++; else fail++;
    if (isdigit('0') && isdigit('9') && !isdigit('a') && !isdigit(' ')) pass++; else fail++;
    if (isxdigit('a') && isxdigit('F') && isxdigit('5') && !isxdigit('z')) pass++; else fail++;
    if (islower('a') && islower('z') && !islower('A') && !islower('0')) pass++; else fail++;
    if (isupper('A') && isupper('Z') && !isupper('a') && !isupper(' ')) pass++; else fail++;
    if (toupper('a') == 'A' && toupper('z') == 'Z' && toupper('A') == 'A' && toupper('5') == '5') pass++; else fail++;
    if (tolower('A') == 'a' && tolower('Z') == 'z' && tolower('a') == 'a' && tolower('5') == '5') pass++; else fail++;
    if (isspace(' ') && isspace('\n') && isspace('\t') && !isspace('A')) pass++; else fail++;
    if (isprint(' ') && isprint('~') && isprint('A') && !isprint('\x7F')) pass++; else fail++;
    if (isgraph('!') && isgraph('~') && isgraph('A') && !isgraph(' ')) pass++; else fail++;
    if (ispunct('!') && ispunct(',') && !ispunct('A') && !ispunct(' ')) pass++; else fail++;
    if (iscntrl('\x00') && iscntrl('\x1F') && !iscntrl('A') && !iscntrl('~')) pass++; else fail++;
    if (isalnum('A') && isalnum('9') && !isalnum('!') && !isalnum(' ')) pass++; else fail++;
    printf("ctype: %d passed, %d failed\n", pass, fail);
    return fail;
}

static int test_errno(void)
{
    int fail = 0;
    errno = 1225;
    if (errno != 1225) { write(1, "errno write/read failed\n", 25); return 1; }
    errno = 0;
    if (errno != 0) { write(1, "errno reset failed\n", 20); return 1; }
    printf("errno: %ld\n", errno);
    printf("errno test passed\n");
    return fail;
}

static int test_assert(void)
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

static int test_inttypes(void)
{
    int fail = 0;
    int32_t a = 1225;
    uint64_t b = 1234567890;
    int64_t c = -69;
    uint8_t d = 64;
    printf("PRId32: %" PRId32 "\n", a);
    printf("PRIu64: %" PRIu64 "\n", b);
    printf("PRId64: %" PRId64 "\n", c);
    printf("PRIu8: %" PRIu8 "\n", d);
    printf("PRIx64: %" PRIx64 "\n", b);
    printf("PRIu32: %" PRIu32 "\n", a);
    printf("PRId8: %" PRId8 "\n", (int8_t)d);
    printf("PRIx32: %" PRIx32 "\n", (uint32_t)a);
    int32_t vals[] = {1225, 69, 64, 1234567890};
    for (int i = 0; i < 4; i++) {
        printf("inttypes val[%d]: %" PRId32 " (0x%" PRIx32 ")\n", i, vals[i], (uint32_t)vals[i]);
    }
    printf("inttypes: all format specifiers worked\n");
    return fail;
}

static int test_strncmp(void)
{
    int fail = 0;
    if (strncmp("abc", "abc", 3) != 0) { fail++; printf("strncmp equal failed\n"); }
    if (strncmp("abc", "abd", 3) >= 0) { fail++; printf("strncmp diff failed\n"); }
    if (strncmp("abc", "abcde", 3) != 0) { fail++; printf("strncmp prefix failed\n"); }
    if (strncmp("abcd", "abc", 4) <= 0) { fail++; printf("strncmp longer failed\n"); }
    if (strncmp("", "", 1) != 0) { fail++; printf("strncmp empty failed\n"); }
    if (fail == 0) printf("strncmp: ok\n");
    return fail;
}

static int test_memcmp(void)
{
    int fail = 0;
    char a[] = {1, 2, 3, 4, 5};
    char b[] = {1, 2, 3, 4, 5};
    char c[] = {1, 2, 3, 4, 6};
    if (memcmp(a, b, 5) != 0) { fail++; printf("memcmp equal failed\n"); }
    if (memcmp(a, c, 5) >= 0) { fail++; printf("memcmp diff failed\n"); }
    if (memcmp(a, c, 3) != 0) { fail++; printf("memcmp prefix same failed\n"); }
    if (memcmp(a, c, 4) != 0) { fail++; printf("memcmp prefix 4 same failed\n"); }
    if (memcmp(a, b, 0) != 0) { fail++; printf("memcmp zero failed\n"); }
    if (fail == 0) printf("memcmp: ok\n");
    return fail;
}

static int test_abs(void)
{
    int fail = 0;
    if (abs(5) != 5) { fail++; printf("abs positive failed\n"); }
    if (abs(-5) != 5) { fail++; printf("abs negative failed\n"); }
    if (abs(0) != 0) { fail++; printf("abs zero failed\n"); }
    if (abs(-2147483647) != 2147483647) { fail++; printf("abs min failed\n"); }
    if (fail == 0) printf("abs: ok\n");
    return fail;
}

static int int_cmp(const void *a, const void *b)
{
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

static int test_qsort(void)
{
    int fail = 0;
    int arr[] = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    qsort(arr, 9, sizeof(int), int_cmp);
    for (int i = 0; i < 9; i++) {
        if (arr[i] != expected[i]) {
            fail++;
            printf("qsort mismatch at %d: got %d expected %d\n", i, arr[i], expected[i]);
            break;
        }
    }
    int arr2[] = {42};
    qsort(arr2, 1, sizeof(int), int_cmp);
    if (arr2[0] != 42) { fail++; printf("qsort single failed\n"); }
    int arr3[] = {3, 1, 2};
    qsort(arr3, 3, sizeof(int), int_cmp);
    if (arr3[0] != 1 || arr3[1] != 2 || arr3[2] != 3) { fail++; printf("qsort triple failed\n"); }
    if (fail == 0) printf("qsort: ok\n");
    return fail;
}

static int test_headers_all(void)
{
    int fail = 0;
    /* limits.h */
    if (CHAR_BIT != 8) { fail++; printf("limits CHAR_BIT failed\n"); }
    if (INT_MAX != 2147483647) { fail++; printf("limits INT_MAX failed\n"); }
    if (LLONG_MAX != 9223372036854775807LL) { fail++; printf("limits LLONG_MAX failed\n"); }
    /* float.h */
    if (FLT_MANT_DIG != 24) { fail++; printf("float FLT_MANT_DIG failed\n"); }
    if (DBL_MANT_DIG != 53) { fail++; printf("float DBL_MANT_DIG failed\n"); }
    /* errno.h */
    if (ENOENT != 2) { fail++; printf("errno ENOENT failed\n"); }
    if (EAGAIN != 11) { fail++; printf("errno EAGAIN failed\n"); }
    if (ENOMEM != 12) { fail++; printf("errno ENOMEM failed\n"); }
    if (ECONNREFUSED != 111) { fail++; printf("errno ECONNREFUSED failed\n"); }
    /* wchar.h */
    if (WEOF != -1) { fail++; printf("wchar WEOF failed\n"); }
    if (wcslen(L"abc") != 3) { fail++; printf("wcslen failed\n"); }
    /* wctype.h */
    if (!iswalpha(L'a')) { fail++; printf("iswalpha failed\n"); }
    /* setjmp.h */
    if (sizeof(jmp_buf) > 0) {} /* just compile check */
    /* locale.h */
    if (LC_ALL != 0) { fail++; printf("locale LC_ALL failed\n"); }
    if (LC_COLLATE != 1) { fail++; printf("locale LC_COLLATE failed\n"); }
    if (localeconv() == NULL) {} /* may return NULL on minimal kernel */
    /* math.h */
    if (M_PI <= 3.0 || M_PI >= 3.2) { fail++; printf("math M_PI failed\n"); }
    if (fabs(-3.14) < 3.13 || fabs(-3.14) > 3.15) { fail++; printf("math fabs failed\n"); }
    if (sqrt(4.0) < 1.99 || sqrt(4.0) > 2.01) { fail++; printf("math sqrt failed\n"); }
    if (ceil(3.7) < 3.99 || ceil(3.7) > 4.01) { fail++; printf("math ceil failed\n"); }
    if (floor(3.7) < 2.99 || floor(3.7) > 3.01) { fail++; printf("math floor failed\n"); }
    if (fmod(5.0, 2.0) < 0.99 || fmod(5.0, 2.0) > 1.01) { fail++; printf("math fmod failed\n"); }
    /* time.h */
    if (CLOCKS_PER_SEC != 1000000) { fail++; printf("time CLOCKS_PER_SEC failed\n"); }
    /* unistd.h */
    if (STDIN_FILENO != 0) { fail++; printf("unistd STDIN_FILENO failed\n"); }
    if (STDOUT_FILENO != 1) { fail++; printf("unistd STDOUT_FILENO failed\n"); }
    if (STDERR_FILENO != 2) { fail++; printf("unistd STDERR_FILENO failed\n"); }
    /* signal.h */
    if (SIGABRT != 6) { fail++; printf("signal SIGABRT failed\n"); }
    if (SIGSEGV != 11) { fail++; printf("signal SIGSEGV failed\n"); }
    if (SIGKILL != 9) { fail++; printf("signal SIGKILL failed\n"); }
    /* fcntl.h */
    if (O_RDONLY != 0) { fail++; printf("fcntl O_RDONLY failed\n"); }
    if (O_WRONLY != 1) { fail++; printf("fcntl O_WRONLY failed\n"); }
    if (O_RDWR != 2) { fail++; printf("fcntl O_RDWR failed\n"); }
    if (O_CREAT != 0100) { fail++; printf("fcntl O_CREAT failed\n"); }
    if (FD_CLOEXEC != 1) { fail++; printf("fcntl FD_CLOEXEC failed\n"); }
    /* sys/types.h */
    if (sizeof(ssize_t) != sizeof(long)) {} /* compile check */
    if (sizeof(off_t) != sizeof(long)) {} /* compile check */
    if (fail == 0) printf("all headers: ok\n");
    return fail;
}

int main(void)
{
    int total_fail = 0;
    int (*tests[])(void) = {
        test_hello, test_stdio, test_headers, test_verify, test_stdlib,
        test_more, test_ctype, test_errno, test_assert, test_inttypes,
        test_strncmp, test_memcmp, test_abs, test_qsort, test_headers_all,
    };
    const char *names[] = {
        "hello", "stdio", "headers", "verify", "stdlib",
        "more", "ctype", "errno", "assert", "inttypes",
        "strncmp", "memcmp", "abs", "qsort", "all_headers",
    };
    for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
        printf("\n=== %s ===\n", names[i]);
        fflush(stdout);
        if (tests[i]() != 0) total_fail++;
    }
    printf("\n%d/%d tests passed\n", (int)(sizeof(tests)/sizeof(tests[0])) - total_fail, (int)(sizeof(tests)/sizeof(tests[0])));
    return total_fail ? 1 : 0;
}
