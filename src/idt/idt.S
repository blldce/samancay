
section .asm

global idt_load

idt_load:
    push ebp        ; push base pointer into stack
    mov ebp, esp    ; move stack pointer into base pointer, so we have a referance to our frame

    mov ebx, [ebp+8]
    lidt [ebx]      ; loads idt

    pop ebp
    ret

