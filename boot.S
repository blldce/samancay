
ORG 0
BITS 16
_start:
    jmp short start
    nop

times 33 db 0

start:
    jmp 0x7c0:step2 ; set code segment 0x7c0

step2:
    cli ; clear interrupts
    mov ax, 0x7c0
    mov ds, ax ; set data segment
    mov es, ax
    mov ax, 0x00
    mov ss, ax ; set stack segment
    mov sp, 0x7c00 ; set pointer to 0x7c00
    sti ; enables interrupts

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