mov ax, 0
mov bx, 1
in cx
cmp cx,0
jz 11
mov dx,ax
add dx,bx
mov ax, bx
mov bx, dx
add cx, -1
jmp 3
out ax
