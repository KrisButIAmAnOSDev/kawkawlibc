#ifndef KAWKAW_STDDEF_H
#define KAWKAW_STDDEF_H

#include "stdint.h"

#define offsetof(type, member) __builtin_offsetof(type, member)

#endif
