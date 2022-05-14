;
; A simple boot sector program that loops forever.
;

[org 0x7c00]

mov bx, hex_prefix
; add bx, 0x7c00        ; not needed anymore

call print_string
; call print_hexa

jmp $

%include "./print_string.asm"

print_hexa:
    pusha
    mov dx, 0xf000
    mov cx, bx
    and bx, ax
    call set_char
    call print_char

loop_hexa:
    shr dx, 4
    mov bx, cx
    and bx, ax

    call set_char
    call print_char
    cmp dx, 0x000f
    je end_print_hexa
    jmp loop_hexa

end_print_hexa:
    popa
    ret

switch_to_char:
    cmp bx, 0x0a
    jl set_char
    add bx, 0x11

set_char:
    add bx, 0x30
    ret


my_string:
    db "Hello World", 0

hex_prefix:
    db "0x", 0


times 510-($-$$) db 0       ; When compiled , our program must fit into 512 bytes ,
                            ; with the last two bytes being the magic number ,
                            ; so here , tell our assembly compiler to pad out our
                            ; program with enough zero bytes ( db 0) to bring us to the
                            ; 510 th byte.

dw 0xaa55                   ; Last two bytes ( one word ) form the magic number ,
                            ; so BIOS knows we are a boot sector.