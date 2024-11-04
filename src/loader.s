    global loader                   ; the entry symbol for ELF

    MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
    FLAGS        equ 0x0            ; multiboot flags
    CHECKSUM     equ -MAGIC_NUMBER  ; calculate the checksum
                                  
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
    

    loader:   
        mov esp, kernel_stack + KERNEL_STACK_SIZE
        extern kmain
        call kmain 
  
    .loop:
        jmp .loop
