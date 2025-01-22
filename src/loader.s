global loader                       ; the entry symbol for ELF

KERNEL_STACK_SIZE equ 0x1000        ; 4 KB      

section .bss

align 0x1000
page_directory:
    resb 0x1000
page_table:
    resb 0x1000

%define page_directory_physical (page_directory - 0xC0000000)
%define page_table_physical (page_table - 0xC0000000)

align 4
kernel_stack:
    resb KERNEL_STACK_SIZE

section .text
    
loader:

    cli         ; disable interrupts

    mov ebp, (kernel_stack - 0xC0000000) + KERNEL_STACK_SIZE   ; set up stack
    mov esp, ebp

    push ebx    ; push adress of multiboot strucure

    mov edi, page_directory_physical
    sub edi, 0xC0000000
    xor eax, eax

    mov ecx, 1024
    rep stosd    

    mov eax, page_table_physical       ; Address of the page table
    or eax, 0x03               ; Present and writable

    mov [page_directory_physical], eax
    mov [page_directory_physical + 0xC00], eax

    mov edi, page_table_physical
    mov ecx, 1024
    xor eax, eax
    or eax, 0x03               ; Set present and writable
.page_loop:
    mov [edi], eax
    add eax, 0x1000            ; Next page frame (4 KB)
    add edi, 4                 ; Move to the next table entry
    loop .page_loop

    mov eax, page_directory_physical
    mov cr3, eax

    mov eax, cr0
    or  eax, 0x80000000
    mov cr0, eax

    add ebp, 0xC0000000
    add esp, 0xC0000000

    lea eax, [higher_half]
    jmp eax

higher_half:

    ; ; protected mode is already enabled, DS is at 0x10
    
    ; extern init_kernel_paging
    ; call init_kernel_paging

    extern kmain
    call kmain

    cli 
    hlt
    mov eax, 0x0b00b1e5
