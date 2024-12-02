global loader                   ; the entry symbol for ELF

MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
FLAGS        equ 0x0            ; multiboot flags
CHECKSUM     equ - MAGIC_NUMBER  ; calculate the  

KERNEL_STACK_SIZE equ 4096      

section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE

section .text:
align 4                         ; the code must be 4 byte aligned
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM 
    

<<<<<<< HEAD
    loader:   
        mov esp, kernel_stack + KERNEL_STACK_SIZE
        extern kmain
        call kmain 
  
    .loop:
        jmp .loop
=======
loader:   
    cli            ; disable interrupts

    extern create_gdt
    call create_gdt
    lgdt [eax]

    ; protected mode is already enabled, DS is at 0x10

    mov esp, kernel_stack + KERNEL_STACK_SIZE
    extern kmain
    call kmain
.loop
    jmp .loop
>>>>>>> 3da34d091c69dd9f488940e152ad9122a279fc87
