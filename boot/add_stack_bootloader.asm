; Read some sectors from the boot disk using our disk_read function
[org 0x7c00]


push 0x0009
push 0x0001
call func_add

mov dx , ax ;Get return value from ax
call print_hex ; we expect to be 0xdada , stored at address 0 x9000

jmp $

%include "print_string.asm" ; Re - use our print_string function
%include "print_hex.asm" ; Re - use our print_hex function
%include "add.asm"

times 510-($-$$) db 0
dw 0xaa55