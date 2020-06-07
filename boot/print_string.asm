print_string:           ; Expects null terminated message in si
    pusha
    mov al,[bx]
    or al,al
    jz  .end
    inc bx
    call print_char
    jmp print_string
.end:
    popa
    retn
 
print_char:
    pusha
    mov ah,0x0E         ; Specifies that we want to write a character to the screen
    mov bl,0x07         ; Specifies output text color.  Not required, but useful to know
    mov bh,0x00         ; Page number.  Leave this alone.
    int 0x10            ; Signal video interrupt to BIOS
    popa
    retn

clear_screen:
    push bp
    mov bp, sp
    pusha

    mov ah, 0x07        ; tells BIOS to scroll down window
    mov al, 0x00        ; clear entire window
    mov bh, 0x07        ; white on black
    mov cx, 0x00        ; specifies top left of screen as (0,0)
    mov dh, 0x18        ; 18h = 24 rows of chars
    mov dl, 0x4f        ; 4fh = 79 cols of chars
    int 0x10            ; calls video interrupt

    popa
    mov sp, bp
    pop bp
    ret

print:
    pusha
    mov si, bx      ;grab the pointer to the data
    mov bh, 0x00        ;page number, 0 again
    mov bl, 0x07        ;foreground color, irrelevant - in text mode
    mov ah, 0x0E        ;print character to TTY
.char:
    mov al, [si]        ;get the current char from our pointer position
    add si, 1           ;keep incrementing si until we see a null char
    or al, 0
    je .return          ;end if the string is done
    int 0x10            ;print the character if we're not done
    jmp .char           ;keep looping
.return:
    popa
    ret
