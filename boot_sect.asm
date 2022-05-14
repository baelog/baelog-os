;
; A simple boot sector program that loops forever.
;

[org 0x7c00]

    ; mov bx, my_string
    ; add bx, 0x7c00        ; not needed anymore
    ; call print_string

    mov dx, 0x1234
    call print_hex

    jmp $

%include "./print_string.asm"
%include "./print_hexa.asm"

my_string:
    db "Hello World\n", 0



; padding and magic number
times 510-($-$$) db 0
dw 0xaa55