.text
.global setjmp
setjmp:
    movq %rbx, 0(%rdi)
    movq %rbp, 8(%rdi)
    movq %r12, 16(%rdi)
    movq %r13, 24(%rdi)
    movq %r14, 32(%rdi)
    movq %r15, 40(%rdi)
    movq (%rsp), %rax
    movq %rax, 48(%rdi)
    movq %rsp, 56(%rdi)
    xorl %eax, %eax
    ret

.text
.global longjmp
longjmp:
    movq 0(%rdi), %rbx
    movq 8(%rdi), %rbp
    movq 16(%rdi), %r12
    movq 24(%rdi), %r13
    movq 32(%rdi), %r14
    movq 40(%rdi), %r15
    movq 56(%rdi), %rsp
    movq 48(%rdi), %rdx
    movq %rdx, (%rsp)
    movl %esi, %eax
    testl %eax, %eax
    jnz 1f
    movl $1, %eax
1:
    ret