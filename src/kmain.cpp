#include "output/frame_buffer.h"
#include "multiboot.h"
#include "std.h"
#include "process.h"

process program;

extern "C" int kmain(multiboot_info_t &multiboot_info) {

    asm("hlt; cli");
    //frame buffer test
    char buffer[] = "frame buffer running";

    fb_write(buffer,sizeof(buffer),LIGHT_GREEN,BLACK);
     
    //serial test
    
    char serial_buffer[] = "serial running\0";
    log(serial_buffer);

    //call program
   
    multiboot_module_t * program_mod = (multiboot_module_t *)multiboot_info.mods_addr;

    fb_write_hex_32(program_mod->mod_start);
    
    program = process(program_mod);  
    unsigned long test_args[] = {2, 3};

    program.args.args = test_args;
    program.args.size = 2;
    // asm("cli; hlt");
    // unsigned long result = program.call();  

    char proces_result_message[] = "function operands sucess:";
    log(proces_result_message);
    // log((test_args[0] + test_args[1]) == result);


    return 0xcafebabe;
}

