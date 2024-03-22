section .text
    global _start

extern printstatement

_start:
    call printstatement

    ; Exit the program
    mov rax, 60         ; syscall: exit
    xor rdi, rdi        ; status: 0
    syscall
