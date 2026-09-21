#include "wctype.h"
#include "string.h"

int iswalpha(wint_t c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
int iswdigit(wint_t c) { return c >= '0' && c <= '9'; }
int iswxdigit(wint_t c) { return iswdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'); }
int iswlower(wint_t c) { return c >= 'a' && c <= 'z'; }
int iswupper(wint_t c) { return c >= 'A' && c <= 'Z'; }
int iswspace(wint_t c) { return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'; }
int iswprint(wint_t c) { return c >= ' ' && c <= '~'; }
int iswgraph(wint_t c) { return c > ' ' && c <= '~'; }
int iswpunct(wint_t c) { return (c > ' ' && c < '0') || (c > '9' && c < 'A') || (c > 'Z' && c < 'a') || (c > 'z' && c <= '~'); }
int iswcntrl(wint_t c) { return (c >= 0 && c <= ' ') || c == 0x7F; }
int iswalnum(wint_t c) { return iswalpha(c) || iswdigit(c); }
int iswblank(wint_t c) { return c == ' ' || c == '\t'; }

wint_t towlower(wint_t c) { return iswupper(c) ? c - 'A' + 'a' : c; }
wint_t towupper(wint_t c) { return iswlower(c) ? c - 'a' + 'A' : c; }

wctr_t wctype(const char *class)
{
    if (strcmp(class, "alpha") == 0) return 1;
    if (strcmp(class, "digit") == 0) return 2;
    if (strcmp(class, "xdigit") == 0) return 3;
    if (strcmp(class, "lower") == 0) return 4;
    if (strcmp(class, "upper") == 0) return 5;
    if (strcmp(class, "space") == 0) return 6;
    if (strcmp(class, "print") == 0) return 7;
    if (strcmp(class, "graph") == 0) return 8;
    if (strcmp(class, "punct") == 0) return 9;
    if (strcmp(class, "cntrl") == 0) return 10;
    if (strcmp(class, "alnum") == 0) return 11;
    if (strcmp(class, "blank") == 0) return 12;
    return 0;
}

int iswctype(wint_t c, wctr_t t)
{
    switch (t) {
    case 1: return iswalpha(c);
    case 2: return iswdigit(c);
    case 3: return iswxdigit(c);
    case 4: return iswlower(c);
    case 5: return iswupper(c);
    case 6: return iswspace(c);
    case 7: return iswprint(c);
    case 8: return iswgraph(c);
    case 9: return iswpunct(c);
    case 10: return iswcntrl(c);
    case 11: return iswalnum(c);
    case 12: return iswblank(c);
    default: return 0;
    }
}
