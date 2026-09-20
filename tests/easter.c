#include "stdio.h"
#include "stdlib.h"

extern int trulyrandomnumberchoosebykawkaw(void);
void thisishowkawkawlibcworks(void);

int main(void)
{
    int answer = trulyrandomnumberchoosebykawkaw();
    printf("the truly random number chosen by kawkaw is: %d\n", answer);
    printf("(RFC 1149.5 / xkcd 221)\n");
    thisishowkawkawlibcworks();
    return 0;
}
