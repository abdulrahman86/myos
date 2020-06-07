func_add:
  push bp     ; save the value of ebp
  mov bp, sp  ;bp now points to the top of the stack
  sub sp, 2  ; space allocated on the stack for return variable
  pusha
  mov ax, [bp+4]      ;get first argument from the stack.
  mov bx, [bp+6]      ;get second argument from the stack.
  add ax, bx
  mov [bp -2], ax ;store return value on stack
  popa
  mov ax, [bp -2] ;store return value in ax
  add sp, 2
  mov sp, bp
  pop bp
  ret
