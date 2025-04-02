global call_process
extern return_registers

call_process:
    mov eax, [esp]
    mov dword [return_registers], eax 
    mov dword [return_registers + 4], ebp
    mov dword [return_registers + 8], esp
    mov eax, cr3
    mov dword [return_registers + 12], eax
    ;save kernel stack for interrupt use

    mov eax, [esp + 4]      ; load page dir
    mov ebx, [esp + 8]      ; Load address
    mov esi, [esp + 12]     ; Load args array pointer
    mov ecx, [esp + 16]     ; Load size (number of arguments)
    
    mov cr3, eax

    mov ebp, 0xc0000000 - 4
    mov esp, ebp
.loop:
    cmp ecx, 0
    je .call
    dec ecx
    push dword [esi + ecx * 4]
    jmp .loop

.call:
    jmp ebx

global return_process
return_process:
    sti 
    mov dword eax, [esp + 4]
    mov dword ebx, [return_registers]
    mov dword ebp, [return_registers + 4]
    mov dword esp, [return_registers + 8]
    mov ecx, [return_registers + 12]
    mov cr3, ecx
    jmp ebx
