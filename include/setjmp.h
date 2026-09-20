#ifndef KAWKAW_SETJMP_H
#define KAWKAW_SETJMP_H

#include "stdint.h"

typedef struct {
    uint64_t rbx;
    uint64_t rbp;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t rip;
    uint64_t rsp;
} jmp_buf[1];

typedef struct {
    uint64_t rbx;
    uint64_t rbp;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t rip;
    uint64_t rsp;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t rax;
} sigjmp_buf[1];

int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int val);
int sigsetjmp(sigjmp_buf env, int savemask);
void siglongjmp(sigjmp_buf env, int val);

#endif