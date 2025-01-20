bits 32

push ebp
mov ebp, esp

mov eax, [esp + 8]
add eax, [esp + 12]

mov esp, ebp
pop ebp
cli
hlt
ret
