    .file   "ula.c"
    .comm   MBR,8,8
    .comm   MAR,8,8
    .comm   AC,8,8
    .comm   MQ,8,8
    .text
    .globl  inicializaULA
    .type   inicializaULA, @function
inicializaULA:
.LFB0:
    .cfi_startproc
    pushq   %rbp
    .cfi_def_cfa_offset 16
    .cfi_offset 6, -16
    movq    %rsp, %rbp
    .cfi_def_cfa_register 6
    movq    $0, AC(%rip)
    movq    $0, MBR(%rip)
    movq    $0, MQ(%rip)
    popq    %rbp
    .cfi_def_cfa 7, 8
    ret
    .cfi_endproc
.LFE0:
    .size   inicializaULA, .-inicializaULA
    .section    .rodata
.LC0:
    .string "ULA:"
.LC1:
    .string "   MBR: %010lX\n"
.LC2:
    .string "    AC: %010lX\n"
.LC3:
    .string "    MQ: %010lX\n"
    .text
    .globl  printUlaRegs
    .type   printUlaRegs, @function
printUlaRegs:
.LFB1:
    .cfi_startproc
    pushq   %rbp
    .cfi_def_cfa_offset 16
    .cfi_offset 6, -16
    movq    %rsp, %rbp
    .cfi_def_cfa_register 6
    movl    $.LC0, %edi
    call    puts
    movq    MBR(%rip), %rdx
    movl    $.LC1, %eax
    movq    %rdx, %rsi
    movq    %rax, %rdi
    movl    $0, %eax
    call    printf
    movq    AC(%rip), %rdx
    movl    $.LC2, %eax
    movq    %rdx, %rsi
    movq    %rax, %rdi
    movl    $0, %eax
    call    printf
    movq    MQ(%rip), %rdx
    movl    $.LC3, %eax
    movq    %rdx, %rsi
    movq    %rax, %rdi
    movl    $0, %eax
    call    printf
    popq    %rbp
    .cfi_def_cfa 7, 8
    ret
    .cfi_endproc
.LFE1:
    .size   printUlaRegs, .-printUlaRegs
    .globl  LoadAcumulator
    .type   LoadAcumulator, @function
LoadAcumulator:
.LFB2:
    .cfi_startproc
    pushq   %rbp
    .cfi_def_cfa_offset 16
    .cfi_offset 6, -16
    movq    %rsp, %rbp
    .cfi_def_cfa_register 6
    movq    AC(%rip), %rax
    movq    %rax, MBR(%rip)
    popq    %rbp
    .cfi_def_cfa 7, 8
    ret
    .cfi_endproc
.LFE2:
    .size   LoadAcumulator, .-LoadAcumulator
    .globl  isAcumulatorNonNegative
    .type   isAcumulatorNonNegative, @function
isAcumulatorNonNegative:
.LFB3:
    .cfi_startproc
    pushq   %rbp
    .cfi_def_cfa_offset 16
    .cfi_offset 6, -16
    movq    %rsp, %rbp
    .cfi_def_cfa_register 6
    movq    AC(%rip), %rax
    movq    %rax, %rdi
    movl    $0, %eax
    call    NEGATIVE
    testl   %eax, %eax
    je  .L5
    movl    $1, %eax
    jmp .L6
.L5:
    movl    $0, %eax
.L6:
    popq    %rbp
    .cfi_def_cfa 7, 8
    ret
    .cfi_endproc
.LFE3:
    .size   isAcumulatorNonNegative, .-isAcumulatorNonNegative
    .section    .rodata
.LC4:
    .string "ERRO: OPCODE NAO DETECTADO"
    .text
    .globl  callArithmeticLogicUnit
    .type   callArithmeticLogicUnit, @function
callArithmeticLogicUnit:
.LFB4:
    .cfi_startproc
    pushq   %rbp
    .cfi_def_cfa_offset 16
    .cfi_offset 6, -16
    movq    %rsp, %rbp
    .cfi_def_cfa_register 6
    pushq   %rbx
    subq    $40, %rsp
    movl    %edi, %eax
    movb    %al, -36(%rbp)
    movq    MAR(%rip), %rax
    movq    %rax, %rdi
    movl    $0, %eax
    .cfi_offset 3, -24
    call    LoadMemoryAddress
    movzbl  -36(%rbp), %eax
    cmpl    $14, %eax
    ja  .L8
    movl    %eax, %eax
    movq    .L23(,%rax,8), %rax
    jmp *%rax
    .section    .rodata
    .align 8
    .align 4
.L23:
    .quad   .L8
    .quad   .L9
    .quad   .L10
    .quad   .L11
    .quad   .L12
    .quad   .L13
    .quad   .L14
    .quad   .L15
    .quad   .L16
    .quad   .L17
    .quad   .L18
    .quad   .L19
    .quad   .L20
    .quad   .L21
    .quad   .L22
    .text
.L9:
    movq    MBR(%rip), %rax
    movq    %rax, AC(%rip)
    jmp .L7
.L10:
    movq    MBR(%rip), %rax
    movq    %rax, %rdi
    call    ABS40
    movq    %rax, AC(%rip)
    jmp .L7
.L11:
    movq    MBR(%rip), %rax
    movq    %rax, %rdi
    call    INV40
    movq    %rax, AC(%rip)
    jmp .L7
.L12:
    movq    MBR(%rip), %rax
    movq    %rax, %rdi
    call    ABS40
    movq    %rax, %rdi
    call    INV40
    movq    %rax, AC(%rip)
    jmp .L7
.L13:
    movq    MQ(%rip), %rax
    movq    %rax, AC(%rip)
    jmp .L7
.L14:
    movq    MBR(%rip), %rax
    movq    %rax, MQ(%rip)
    jmp .L7
.L15:
    movq    AC(%rip), %rdx
    movq    MBR(%rip), %rax
    addq    %rdx, %rax
    movq    %rax, AC(%rip)
    jmp .L7
.L16:
    movq    MBR(%rip), %rax
    movq    %rax, %rdi
    movl    $0, %eax
    call    NEGATIVE
    testl   %eax, %eax
    je  .L25
    movq    AC(%rip), %rbx
    movq    MBR(%rip), %rax
    movq    %rax, %rdi
    call    ABS40
    movq    %rbx, %rdx
    subq    %rax, %rdx
    movq    %rdx, %rax
    movq    %rax, AC(%rip)
    jmp .L7
.L25:
    movq    MBR(%rip), %rax
    movq    %rax, %rdi
    call    ABS40
    movq    %rax, %rdx
    movq    AC(%rip), %rax
    addq    %rdx, %rax
    movq    %rax, AC(%rip)
    jmp .L7
.L17:
    movq    AC(%rip), %rdx
    movq    MBR(%rip), %rax
    movq    %rdx, %rcx
    subq    %rax, %rcx
    movq    %rcx, %rax
    movq    %rax, AC(%rip)
    jmp .L7
.L18:
    movq    MBR(%rip), %rax
    movq    %rax, %rdi
    movl    $0, %eax
    call    NEGATIVE
    testl   %eax, %eax
    je  .L27
    movq    MBR(%rip), %rax
    movq    %rax, %rdi
    call    ABS40
    movq    %rax, %rdx
    movq    AC(%rip), %rax
    addq    %rdx, %rax
    movq    %rax, AC(%rip)
    jmp .L7
.L27:
    movq    AC(%rip), %rbx
    movq    MBR(%rip), %rax
    movq    %rax, %rdi
    call    ABS40
    movq    %rbx, %rdx
    subq    %rax, %rdx
    movq    %rdx, %rax
    movq    %rax, AC(%rip)
    jmp .L7
.L19:
    movq    MBR(%rip), %rax
    movq    %rax, %rdi
    movl    $0, %eax
    call    NEGATIVE
    testl   %eax, %eax
    je  .L29
    movq    MQ(%rip), %rax
    movq    %rax, %rdi
    movl    $0, %eax
    call    NEGATIVE
    testl   %eax, %eax
    je  .L30
.L29:
    movq    MBR(%rip), %rax
    movq    %rax, %rdi
    movl    $0, %eax
    call    NEGATIVE
    testl   %eax, %eax
    jne .L31
    movq    MQ(%rip), %rax
    movq    %rax, %rdi
    movl    $0, %eax
    call    NEGATIVE
    testl   %eax, %eax
    je  .L31
.L30:
    movq    MBR(%rip), %rax
    movq    %rax, %rdi
    call    ABS40
    movq    %rax, %rbx
    movq    MQ(%rip), %rax
    movq    %rax, %rdi
    call    ABS40
    imulq   %rbx, %rax
    movq    %rax, %rdi
    call    INV40
    movq    %rax, -24(%rbp)
    movq    -24(%rbp), %rax
    movq    %rax, %rdi
    call    ABS40
    movq    %rax, MQ(%rip)
    shrq    $40, -24(%rbp)
    movq    -24(%rbp), %rax
    movq    %rax, AC(%rip)
    jmp .L7
.L31:
    movq    MBR(%rip), %rax
    movq    %rax, %rdi
    call    ABS40
    movq    %rax, %rbx
    movq    MQ(%rip), %rax
    movq    %rax, %rdi
    call    ABS40
    imulq   %rbx, %rax
    movq    %rax, -24(%rbp)
    movq    -24(%rbp), %rax
    movq    %rax, %rdi
    call    ABS40
    movq    %rax, MQ(%rip)
    shrq    $40, -24(%rbp)
    movq    -24(%rbp), %rax
    movq    %rax, AC(%rip)
    jmp .L7
.L20:
    movq    MBR(%rip), %rax
    movq    %rax, %rdi
    movl    $0, %eax
    call    NEGATIVE
    testl   %eax, %eax
    je  .L33
    movq    MQ(%rip), %rax
    movq    %rax, %rdi
    movl    $0, %eax
    call    NEGATIVE
    testl   %eax, %eax
    je  .L34
.L33:
    movq    MBR(%rip), %rax
    movq    %rax, %rdi
    movl    $0, %eax
    call    NEGATIVE
    testl   %eax, %eax
    jne .L35
    movq    MQ(%rip), %rax
    movq    %rax, %rdi
    movl    $0, %eax
    call    NEGATIVE
    testl   %eax, %eax
    je  .L35
.L34:
    movq    AC(%rip), %rax
    movq    %rax, %rdi
    call    ABS40
    movq    %rax, %rbx
    movq    MBR(%rip), %rax
    movq    %rax, %rdi
    call    ABS40
    movq    %rax, -48(%rbp)
    movq    %rbx, %rax
    movq    %rax, %rdx
    sarq    $63, %rdx
    idivq   -48(%rbp)
    movq    %rdx, %rcx
    movq    %rcx, %rax
    movq    %rax, AC(%rip)
    movq    AC(%rip), %rax
    movq    %rax, %rdi
    call    ABS40
    movq    %rax, %rbx
    movq    MBR(%rip), %rax
    movq    %rax, %rdi
    call    ABS40
    movq    %rax, -48(%rbp)
    movq    %rbx, %rax
    movq    %rax, %rdx
    sarq    $63, %rdx
    idivq   -48(%rbp)
    movq    %rax, %rdi
    call    INV40
    movq    %rax, MQ(%rip)
    jmp .L7
.L35:
    movq    AC(%rip), %rax
    movq    %rax, %rdi
    call    ABS40
    movq    %rax, %rbx
    movq    MBR(%rip), %rax
    movq    %rax, %rdi
    call    ABS40
    movq    %rax, -48(%rbp)
    movq    %rbx, %rax
    movq    %rax, %rdx
    sarq    $63, %rdx
    idivq   -48(%rbp)
    movq    %rdx, %rcx
    movq    %rcx, %rax
    movq    %rax, AC(%rip)
    movq    AC(%rip), %rax
    movq    %rax, %rdi
    call    ABS40
    movq    %rax, %rbx
    movq    MBR(%rip), %rax
    movq    %rax, %rdi
    call    ABS40
    movq    %rax, -48(%rbp)
    movq    %rbx, %rax
    movq    %rax, %rdx
    sarq    $63, %rdx
    idivq   -48(%rbp)
    movq    %rax, MQ(%rip)
    jmp .L7
.L22:
    movq    AC(%rip), %rax
    addq    %rax, %rax
    movq    %rax, AC(%rip)
    jmp .L7
.L21:
    movq    AC(%rip), %rax
    shrq    %rax
    movq    %rax, AC(%rip)
    jmp .L7
.L8:
    movl    $.LC4, %eax
    movq    %rax, %rdi
    movl    $0, %eax
    call    printf
    nop
.L7:
    addq    $40, %rsp
    popq    %rbx
    popq    %rbp
    .cfi_def_cfa 7, 8
    ret
    .cfi_endproc
.LFE4:
    .size   callArithmeticLogicUnit, .-callArithmeticLogicUnit
    .ident  "GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
    .section    .note.GNU-stack,"",@progbits
