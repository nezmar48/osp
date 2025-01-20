global loader_func
global loader_func_end

align 4
loader_func:
    lea ebp, [rel loader_func_end + 0x1000]

    mov ebx, [esp + 4]      ; Load entry label address
    mov ecx, [esp + 8]      ; Load args array pointer
    mov edx, [esp + 12]     ; Load size (number of arguments)

    mov eax, edx
.loop:
    cmp eax, 0
    je .call
    dec eax
    push dword [ecx + eax * 4]
    jmp .loop

.call:
    mov eax, cr0      
    or eax, 0x80000000
    mov cr0, eax    

    call ebx
loader_func_end:
