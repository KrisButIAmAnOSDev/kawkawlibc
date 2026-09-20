.text
.global _start
_start:
    movq (%rsp), %r12
    leaq 8(%rsp), %r13

    testq $0xF, %rsp
    jz 1f
    subq $8, %rsp
1:
    lea __init_array_start(%rip), %r14
    lea __init_array_end(%rip), %r15
2:
    cmpq %r14, %r15
    je 3f
    call *(%r14)
    addq $8, %r14
    jmp 2b
3:
    movq %r12, %rdi
    movq %r13, %rsi
    call main
    movl %eax, %r14d
    pushq %r14

    lea __fini_array_start(%rip), %r14
    lea __fini_array_end(%rip), %r15
4:
    cmpq %r14, %r15
    je 5f
    subq $8, %r15
    call *(%r15)
    jmp 4b
5:
    popq %r14
    movl %r14d, %edi
    call exit
