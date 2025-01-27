global memcopy

memcopy:
    mov esi, [esp + 4]  ;original adress
    mov edi, [esp + 8]  ;destination adress
    mov ecx, [esp + 12] ;size
.loop:
    mov dword eax, [esi + ecx * 4]
    mov dword [edi + ecx * 4], eax
    dec ecx
    jns .loop

    ret

