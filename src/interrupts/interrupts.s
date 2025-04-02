%macro isr_err_stub 1-2
isr_stub_%+%1:
    %if %0 > 1              ; Check if a second argument was provided
        pushad
        push %1
        extern %2
        call %2             ; Call the provided handler
        pop eax
        popad
        add esp, 4      ;discard error code
    %else
        mov eax, 0xDEADBEEF
        mov ebx, %1
        cli
        hlt
    %endif
    iret
%endmacro

%macro isr_no_err_stub 1-2
isr_stub_%+%1:
    %if %0 > 1              ; Check if a second argument was provided
        pushad
        push %1 
        extern %2
        call %2             ; Call the provided handler
        pop eax
        popad
    %else
        mov eax, 0xDEADBEEF
        mov ebx, %1
        cli
        hlt
    %endif
    iret
    %endmacro


isr_no_err_stub 0    ; 0x0
isr_no_err_stub 1    ; 0x1
isr_no_err_stub 2    ; 0x2
isr_no_err_stub 3    ; 0x3
isr_no_err_stub 4    ; 0x4
isr_no_err_stub 5    ; 0x5
isr_no_err_stub 6    ; 0x6
isr_no_err_stub 7    ; 0x7
isr_err_stub    8    ; 0x8 
isr_no_err_stub 9    ; 0x9
isr_err_stub    10   ; 0xA
isr_err_stub    11   ; 0xB
isr_err_stub    12   ; 0xC
isr_err_stub    13   ; 0xD
isr_err_stub    14, page_fault  ; 0xE
isr_no_err_stub 15   ; 0xF
isr_no_err_stub 16   ; 0x10
isr_err_stub    17   ; 0x11
isr_no_err_stub 18   ; 0x12
isr_no_err_stub 19   ; 0x13
isr_no_err_stub 20   ; 0x14
isr_no_err_stub 21   ; 0x15
isr_no_err_stub 22   ; 0x16
isr_no_err_stub 23   ; 0x17
isr_no_err_stub 24   ; 0x18
isr_no_err_stub 25   ; 0x19
isr_no_err_stub 26   ; 0x1A
isr_no_err_stub 27   ; 0x1B
isr_no_err_stub 28   ; 0x1C
isr_no_err_stub 29   ; 0x1D
isr_no_err_stub 30   ; 0x1E
isr_no_err_stub 31   ; 0x1F
isr_no_err_stub 32, PIC_stub ; 0x20 (master PIC)
isr_no_err_stub 33, PIC_stub ; 0x21
isr_no_err_stub 34, PIC_stub ; 0x22
isr_no_err_stub 35, PIC_stub ; 0x23
isr_no_err_stub 36, PIC_stub ; 0x24
isr_no_err_stub 37, PIC_stub ; 0x25
isr_no_err_stub 38, PIC_stub ; 0x26
isr_no_err_stub 39, PIC_stub ; 0x27
isr_no_err_stub 40, PIC_stub ; 0x28 (slave PIC)
isr_no_err_stub 41, PIC_stub ; 0x29
isr_no_err_stub 42, PIC_stub ; 0x2A
isr_no_err_stub 43, PIC_stub ; 0x2B
isr_no_err_stub 44, PIC_stub ; 0x2C
isr_no_err_stub 45, PIC_stub ; 0x2D
isr_no_err_stub 46, PIC_stub ; 0x2E
isr_no_err_stub 47, PIC_stub ; 0x2F
isr_no_err_stub 48, system_call   ; 0x30
isr_no_err_stub 49, test_interrupt ; 0x31


section .data
    IDT_ENTRIES equ 0x32

global isr_stub_table
isr_stub_table:
%assign i 0 
%rep    IDT_ENTRIES 
    dd isr_stub_%+i 
%assign i i+1 
%endrep
