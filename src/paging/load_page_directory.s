section .text
global loadPageDirectory

loadPageDirectory:
    push ebp          
    mov ebp, esp     
    mov eax, [ebp + 8] 
    mov cr3, eax      
    mov esp, ebp     
    pop ebp         
    ret            
