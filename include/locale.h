#ifndef KAWKAW_LOCALE_H
#define KAWKAW_LOCALE_H

#include "stddef.h"

#define LC_ALL      0
#define LC_COLLATE  1
#define LC_CTYPE    2
#define LC_MONETARY 3
#define LC_NUMERIC  4
#define LC_TIME     5
#define LC_MESSAGES 6

struct lconv {
    const char *decimal_point;
    const char *thousands_sep;
    const char *grouping;
    const char *int_curr_symbol;
    const char *currency_symbol;
    const char *mon_decimal_point;
    const char *mon_thousands_sep;
    const char *mon_grouping;
    const char *negative_sign;
    const char *positive_sign;
    int frac_digits;
    int p_cs_precedes;
    int p_sep_by_space;
    int n_cs_precedes;
    int n_sep_by_space;
    int p_sign_posn;
    int n_sign_posn;
};

char *setlocale(int category, const char *locale);
struct lconv *localeconv(void);

#endif