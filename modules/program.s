bits 32

push ebp
mov ebp, esp

mov eax, [esp + 4]
add eax, [esp + 8]

push eax
int 32
