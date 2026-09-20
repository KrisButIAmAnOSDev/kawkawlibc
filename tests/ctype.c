#include "ctype.h"
#include "stdio.h"

int main(void)
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
    return fail ? 1 : 0;
}
