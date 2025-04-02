#include "gdt.h"
#include "multiboot.h"
#include "std.h"
#include "process.h"
#include "interrupts.h"
#include "paging.h"

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
    init_heap(KERNEL_OFFSET + kernel_size * 0x400000, KERNEL_OFFSET + (kernel_size + 1) * 0x400000);

    //frame buffer test
    frame_buffer fb;
    fb.write("frame buffer running \n");
     
    //serial test
    
    log("serial running");

    //malloc test
    malloc_test();

    //call program

    multiboot_module_t * program_mod = add_offset((multiboot_module_t *)multiboot_info->mods_addr);

    fb.write(String(program_mod->mod_start));
    log(program_mod->mod_start);

    process program(program_mod);

    unsigned long test_args[] = {2, 3};

    program.args.args = test_args;
    program.args.size = 2;

    unsigned long result = program.call();  

    log("function operands sucess:");
    log((test_args[0] + test_args[1]) == result);

    return 0xcafebabe;
}

