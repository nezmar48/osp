global call_process

call_process:
    push ebp
    mov ebp, esp

    mov ebx, [ebp + 8]      ; Load address
    mov ecx, [ebp + 12]     ; Load args array pointer
    mov edx, [ebp + 16]     ; Load size (number of arguments)

    mov eax, edx
.loop:
    cmp eax, 0
    je .call
    dec eax
    push dword [ecx + eax * 4]
    jmp .loop

.call:
    cli
    hlt
    call ebx
    mov esp, ebp
    pop ebp 
    ret
