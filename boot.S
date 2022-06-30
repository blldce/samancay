
ORG 0
BITS 16
_start:
    jmp short start
    nop

times 33 db 0

start:
    jmp 0x7c0:step2 ; set code segment 0x7c0


handle_zero: ; responsible for handling interrupt 0
    mov ah, 0eh
    mov al, 'A'
    mov bx, 0x00
    int 0x10
    iret ; interrupt return

handle_one:
    mov ah, 0eh
    mov al, 'B'
    mov bx, 0x00
    int 0x10
    iret ; interrupt return

step2:
    cli ; clear interrupts
    mov ax, 0x7c0 ; hold address
    mov ds, ax ; set data segment
    mov es, ax
    mov ax, 0x00 ; hold address
    mov ss, ax ; set stack segment
    mov sp, 0x7c00 ; set pointer to 0x7c00
    sti ; enables interrupts

    ; https://wiki.osdev.org/Exceptions
    mov word[ss:0x00], handle_zero ; interrupts start with 0x0 memory address
    mov word[ss:0x02], 0x7c0 ; 

    mov word[ss:0x04], handle_one 
    mov word[ss:0x06], 0x7c0

    int 0 ; interrupt  0 (divide by zero interrupt)

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