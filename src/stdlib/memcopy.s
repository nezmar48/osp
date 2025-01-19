global memcopy

memcopy:
    mov ebx, [esp + 4]  ;original adress
    mov ecx, [esp + 8]  ;destination adress
    mov edx, [esp + 12] ;size

.loop:
    mov dword eax, [ebx + edx * 4]
    mov dword [ecx + edx * 4], eax
    dec edx
    jns .loop

    ret

