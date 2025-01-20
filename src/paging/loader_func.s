global loader_func
global loader_func_end

align 4
loader_func:
    lea ebp, [rel loader_func_end + 0x1000]

    mov eax, [esp + 4]      ; page dir 
    mov ebx, [esp + 8]      ; Load entry label address
    mov ecx, [esp + 12]     ; Load args array pointer
    mov edx, [esp + 16]     ; Load size (number of arguments)

    mov cr3, eax

    mov eax, edx
.loop:
    cmp eax, 0
    je .call
    dec eax
    push dword [ecx + eax * 4]
    jmp .loop

.call:
    call ebx
loader_func_end:
