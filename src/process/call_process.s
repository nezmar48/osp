global call_process

call_process:
    ;save kernel stack for interrupt use

    mov eax, [esp + 4]      ; load page dir
    mov ebx, [esp + 8]      ; Load address
    mov edi, [esp + 12]     ; Load args array pointer
    mov ecx, [esp + 16]     ; Load size (number of arguments)
    
    mov cr3, eax

    mov ebp, 0xc0000000 - 4
    mov esp, ebp

.loop:
    cmp ecx, 0
    je .call
    dec ecx
    push dword [edi + ecx * 4]
    jmp .loop

.call:
    jmp ebx
    mov esp, ebp
    pop ebp 
    ret
