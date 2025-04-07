#include "gdt.h"
#include "io.h"
#include "multiboot.h"
#include "std.h"
#include "interrupts.h"
#include "paging.h"
#include "shell.h"

void shell_main();

extern "C" int kmain(multiboot_info_t * multiboot_info) {

    multiboot_info = add_offset(multiboot_info);

    unsigned long gdt = create_gdt();
    asm volatile (
        "lgdt (%0);"
        :
        : "r" (gdt)
        : "memory"
    );

    unsigned long idt = idt_init();
    // asm volatile ("hlt");
    asm volatile (
        "lidt (%0);"
        "sti;"
        "int $0x31;"
        :
        : "r" (idt)
        : "memory"
    );

    init_kernel_paging(); 
    init_heap(KERNEL_OFFSET + kernel_size * 0x400000, KERNEL_OFFSET + (kernel_size + 1) * 0x400000);

    //malloc test
    malloc_test();

    keyboard_init();

    //call program

    init_shell(multiboot_info);

    shell_main();
   
    return 0xcafebabe;
}

