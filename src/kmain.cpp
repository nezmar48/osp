#include "output/frame_buffer.h"
#include "output/serial_port.h"
#include "output/frame_buffer.h"
#include "multiboot.h"
#include "stdlib/string.cpp"
#include "process.cpp"

extern "C" int kmain(multiboot_info_t &multiboot_info) {

    //frame buffer test
    char buffer[] = "frame buffer running";

    fb_write(buffer,sizeof(buffer),LIGHT_GREEN,BLACK);
     
    //serial test
    
    serial_configure(SERIAL_COM1_BASE, Baud_115200);
    char serial_buffer[] = "serial running";
    serial_write(SERIAL_COM1_BASE, serial_buffer, sizeof(serial_buffer));

    //call program
    
    multiboot_module_t * program_mod = (multiboot_module_t *)multiboot_info.mods_addr;

    fb_write_hex_32(program_mod->mod_start);
    
    process program(program_mod);

    program.call();    

    return 0xcafebabe;
}

