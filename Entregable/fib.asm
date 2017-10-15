mov bh, 220     
mov [bh],0      
mov ax, [bh]    
add [bh], 1     
mov bx, [bh]    
in cx           
cmp cx,0        
jz 14           
mov dx,ax
add dx,bx        
mov ax, bx      
mov bx, dx      
add cx, -1        
jmp 6               
sti                  
out ax          
