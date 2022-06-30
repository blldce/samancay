
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
    mov ax, 0x7c0 ; hold address
    mov ds, ax ; set data segment
    mov es, ax ; extra segment
    mov ax, 0x00 ; hold address
    mov ss, ax ; set stack segment
    mov sp, 0x7c00 ; set pointer to 0x7c00
    sti ; enables interrupts

    ; https://www.ctyme.com/intr/int.htm
    mov ah, 2 ; read sector
    mov al, 1 ; one sector read
    mov ch, 0 ; cylinder low eight bits
    mov cl, 2 ; read sector two
    mov dh, 0 ; head number
    mov bx, buffer
    int 0x13 ; invoke interrupt 13
    jc error ; jump carry

    mov si, buffer
    call print

    jmp $ ; infinitive loop

error:
    mov si, error_message
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

error_message: db 'Failed to load sector', 0

times 510-($ - $$) db 0 ; fill 510 bytes with zeroes.
dw 0xAA55 ; boot signature

buffer: