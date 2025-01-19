section .text
global enablePaging

enablePaging:
    mov eax, cr0      
    or eax, 0x80000000
    mov cr0, eax     
    ret           
