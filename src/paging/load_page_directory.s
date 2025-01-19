section .text
global loadPageDirectory

loadPageDirectory:
    mov eax, [esp + 4] 
    mov cr3, eax      
    ret            
