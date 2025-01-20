section .text
global disable_paging
disable_paging:
    mov eax, cr0      
    xor eax, 0x80000000
    mov cr0, eax     
    ret       
