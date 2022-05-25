
print_string:
    pusha
    mov ah, 0x0e

string_loop:
    mov al, [bx]
    int 0x10
    add bx, 1
    cmp al, 0x0000
    jg string_loop
    popa
    ret

print_char:
    pusha
    mov ah, 0x0e
    mov al, [bx]
    int 0x10
    popa
    ret