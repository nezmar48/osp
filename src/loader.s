global loader                       ; the entry symbol for ELF

KERNEL_STACK_SIZE equ 0x1000        ; 4 KB      

section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE

section .text
    
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
    
    extern init_kernel_paging
    call init_kernel_paging

    extern kmain
    call kmain

    cli 
    hlt
    mov eax, 0x0b00b1e5
