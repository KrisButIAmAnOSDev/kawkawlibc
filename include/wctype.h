#ifndef KAWKAW_WCTYPE_H
#define KAWKAW_WCTYPE_H

#include "wchar.h"

typedef int wctr_t;

wctr_t wctype(const char *class);
int iswctype(wint_t c, wctr_t t);
int iswalpha(wint_t c);
int iswdigit(wint_t c);
int iswxdigit(wint_t c);
int iswlower(wint_t c);
int iswupper(wint_t c);
int iswspace(wint_t c);
int iswprint(wint_t c);
int iswgraph(wint_t c);
int iswpunct(wint_t c);
int iswcntrl(wint_t c);
int iswalnum(wint_t c);
int iswblank(wint_t c);
wint_t towlower(wint_t c);
wint_t towupper(wint_t c);

#endif