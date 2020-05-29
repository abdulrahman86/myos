; Ensures that we jump straight into the kernel ’s entry function.
[bits 32] ; We ’re in protected mode by now , so use 32 - bit instructions.
[extern main] ; Declate that we will be referencing the external symbol ’main ’,
; so the linker can substitute the final address

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f ; the color byte for each character


mov ebx , MSG_BEGINNING_ENTER_KERNEL ; Use our 32 - bit print routine to
call print_string_pm ; announce we are in protected mode
mov ebx , MSG_ENTER_KERNEL ; Use our 32 - bit print routine to
call print_string_pm ; announce we are in protected mode
call main ; invoke main () in our C kernel
jmp $ ; Hang forever when we return from the kernel
MSG_BEGINNING_ENTER_KERNEL db "Beginning to enter Kernel..." , 0
MSG_ENTER_KERNEL db "Entering Kernel..." , 0

print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY

print_string_pm_loop:
    mov al, [ebx] ; [ebx] is the address of our character
    mov ah, WHITE_ON_BLACK

    cmp al, 0 ; check if end of string
    je print_string_pm_done

    mov [edx], ax ; store character + attribute in video memory
    add ebx, 1 ; next char
    add edx, 2 ; next video memory position

    jmp print_string_pm_loop

print_string_pm_done:
    popa
    ret