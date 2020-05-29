[org 0x7c00]
mov bx,HELLO_MSG
call print

;call clear_screen

mov bx,GOODBYE_MSG
call print


jmp $

%include "print_string.asm" ; Re - use our print_string function


; Data
HELLO_MSG db 'Hello, World!' , 0 ; <-- The zero on the end tells our routine

GOODBYE_MSG db 'Goodbye ! Bye bye bye world', 0

; Padding and magic number.
times 510-($-$$) db 0
dw 0xaa55