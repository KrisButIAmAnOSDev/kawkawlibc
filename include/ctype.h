#ifndef KAWKAW_CTYPE_H
#define KAWKAW_CTYPE_H

#include "kawkawlibc_config.h"
#include "stddef.h"

#if ENABLE_CTYPE

int isalpha(int c);
int isdigit(int c);
int isxdigit(int c);
int islower(int c);
int isupper(int c);
int toupper(int c);
int tolower(int c);
int isspace(int c);
int isprint(int c);
int isgraph(int c);
int ispunct(int c);
int iscntrl(int c);
int isalnum(int c);
int isblank(int c);

#endif

#endif
