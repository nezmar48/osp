global loader                       ; the entry symbol for ELF

MAGIC_NUMBER    equ 0x1BADB002      ; define the magic number constant
FLAGS           equ 0x00000001      ; bit 0 align modules at 4KB
CHECKSUM        equ -(MAGIC_NUMBER + FLAGS)

KERNEL_STACK_SIZE equ 0x1000        ; 4 KB      

section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE

section .text
align 4                         ; the code must be 4 byte aligned
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM 
    
loader:
    cli         ; disable interrupts
    
    mov ebp, kernel_stack + KERNEL_STACK_SIZE   ; set up stack
    mov esp, ebp

    push ebx    ; push adress of multiboot strucure

    extern create_gdt
    call create_gdt
    lgdt [eax]

    extern idt_init
    call idt_init
    lidt [eax]
    sti            ; enable interrupts
    int 32 ; test interrupts

    ; protected mode is already enabled, DS is at 0x10

    extern kmain
    call kmain
.loop:
    jmp .loop
