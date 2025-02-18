#include "gdt.h"
#include "output.h"
#include "multiboot.h"
#include "std.h"
#include "process.h"
#include "interrupts.h"
#include "paging.h"

page_directory_t process_page_dir;
page_table_t process_page_table_main;
page_directory_t process_page_table_stack;
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
    asm volatile (
        "lidt (%0);"
        "sti;"
        "int $33;"
        :
        : "r" (idt)
        : "memory"
    );

    init_kernel_paging(); 
    init_heap(KERNEL_OFFSET + kernel_size * 0x400000);

    //frame buffer test
    char buffer[] = "frame buffer running";

    fb_write(buffer,sizeof(buffer),LIGHT_GREEN,BLACK);
     
    //serial test
    
    char serial_buffer[] = "serial running\0";
    log(serial_buffer);

    //malloc test
    malloc_test();

    //call program

    multiboot_module_t * program_mod = add_offset((multiboot_module_t *)multiboot_info->mods_addr);

    fb_write_hex_32(program_mod->mod_start);
    
    process program(program_mod, &process_page_dir, &process_page_table_main, &process_page_table_stack);

    unsigned long test_args[] = {2, 3};

    program.args.args = test_args;
    program.args.size = 2;

    unsigned long result = program.call();  

    char proces_result_message[] = "function operands sucess:";
    log(proces_result_message);
    log((test_args[0] + test_args[1]) == result);

    return 0xcafebabe;
}

