#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "kawkawlibc.h"
#include "stat.h"

int main(void)
{
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

    return 0;
}
