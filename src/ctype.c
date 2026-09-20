#include "ctype.h"

int isalpha(int c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
int isdigit(int c) { return c >= '0' && c <= '9'; }
int isxdigit(int c) { return isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'); }
int islower(int c) { return c >= 'a' && c <= 'z'; }
int isupper(int c) { return c >= 'A' && c <= 'Z'; }
int toupper(int c) { return islower(c) ? c - 'a' + 'A' : c; }
int tolower(int c) { return isupper(c) ? c - 'A' + 'a' : c; }
int isspace(int c) { return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'; }
int isprint(int c) { return c >= ' ' && c <= '~'; }
int isgraph(int c) { return c > ' ' && c <= '~'; }
int ispunct(int c) { return (c > ' ' && c < '0') || (c > '9' && c < 'A') || (c > 'Z' && c < 'a') || (c > 'z' && c <= '~'); }
int iscntrl(int c) { return (c >= 0 && c <= ' ') || c == 0x7F; }
int isalnum(int c) { return (isalpha(c) || isdigit(c)); }
int isblank(int c) { return c == ' ' || c == '\t'; }
