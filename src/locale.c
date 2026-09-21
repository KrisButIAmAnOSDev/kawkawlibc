#include "locale.h"

static struct lconv _lconv;

static void _init_lconv(void)
{
    static int done = 0;
    if (done) return;
    _lconv.decimal_point = ".";
    _lconv.thousands_sep = "";
    _lconv.grouping = "";
    _lconv.int_curr_symbol = "";
    _lconv.currency_symbol = "";
    _lconv.mon_decimal_point = "";
    _lconv.mon_thousands_sep = "";
    _lconv.mon_grouping = "";
    _lconv.negative_sign = "";
    _lconv.positive_sign = "";
    _lconv.frac_digits = -1;
    _lconv.p_cs_precedes = 0;
    _lconv.p_sep_by_space = 0;
    _lconv.n_cs_precedes = 0;
    _lconv.n_sep_by_space = 0;
    _lconv.p_sign_posn = 0;
    _lconv.n_sign_posn = 0;
    done = 1;
}

char *setlocale(int category, const char *locale)
{
    (void)category;
    (void)locale;
    _init_lconv();
    return NULL;
}

struct lconv *localeconv(void)
{
    _init_lconv();
    return &_lconv;
}
