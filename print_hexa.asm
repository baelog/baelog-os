;
; almost every line form https://gist.github.com/jsutlovic/7f1c5629deef4543bb47
; only one is missing cause it's useless
;

print_hex:          ; using dx as parametter
    pusha
    
    mov cx,4

char_loop:
    dec cx
    
    mov ax, dx
    shr dx, 4
    and ax, 0xf
    
    mov bx, HEX_OUT   ; set bx to the memory address of our string
    add bx, 2
    add bx, cx
    
    cmp ax,0xa
    jl set_letter
    add byte [bx], 7

set_letter:
    add byte [bx], al ; ax = ha + al -> lower ax added to lower bx

    cmp cx,0
    je print_hex_done
    jmp char_loop

print_hex_done:
    mov bx, HEX_OUT
    call print_string

    popa
    ret

; global variables
HEX_OUT:
    db '0x0000',0