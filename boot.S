
ORG 0X7c00
BITS 16

start:
    mov si, message    ; move message addr into si register
    call print
    jmp $ ; infinitive loop


print:
    mov bx, 0
.loop:
    lodsb ; loads si register point to.
    cmp al, 0
    je .done
    call print_char
    jmp .loop
.done:
    ret

print_char:
    mov ah, 0eh
    int 0x10 ; BIOS TTY output interrupt. Display a characater on vga.
    ret

message: db 'Hello World', 0

times 510-($ - $$) db 0 ; fill 510 bytes with zeroes.
dw 0xAA55 ; boot signature