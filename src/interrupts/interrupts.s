%macro isr_err_stub 1-2
isr_stub_%+%1:
    %if %0 > 1              ; Check if a second argument was provided
        pusha
        extern %2
        call %2             ; Call the provided handler
        popa
    %else
        pusha
        mov eax, 0xDEADBEEF
        mov ebx, %1
        cli
        hlt
        popa
    %endif
    iret
%endmacro

%macro isr_no_err_stub 1-2
isr_stub_%+%1:
    %if %0 > 1              ; Check if a second argument was provided
        pusha
        extern %2
        call %2             ; Call the provided handler
        popa
    %else
        pusha
        mov eax, 0xDEADBEEF
        mov ebx, %1
        cli
        hlt
        popa
    %endif
    iret
%endmacro

isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14, page_fault_handler
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31
isr_no_err_stub 32, test_exception_handler

section .data
    IDT_ENTRIES equ 33

global isr_stub_table
isr_stub_table:
%assign i 0 
%rep    IDT_ENTRIES 
    dd isr_stub_%+i 
%assign i i+1 
%endrep
