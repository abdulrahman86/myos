; Read some sectors from the boot disk using our disk_read function
[org 0x7c00]


mov ax, 0x0001
mov bx, 0x0001
add ax, bx
mov dx , ax ; Print out the first loaded word , which
call print_hex ; we expect to be 0xdada , stored at address 0 x9000

jmp $

%include "print_string.asm" ; Re - use our print_string function
%include "print_hex.asm" ; Re - use our print_hex function

times 510-($-$$) db 0
dw 0xaa55