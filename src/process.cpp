#include "paging/paging.h"
#include "std.h"
#include "process.h"

extern "C" unsigned long call_process(void * address, unsigned long * args, unsigned long size);

int process::ids = 0;

process::process(multiboot_module_t *module) {
    this->id = ids++; 
    this->module = *module;
    // init_page_directory((this->page_dir), PRESENT | READ_WRITE | USER);
    init_page_table(this->first_page_table, READ_WRITE | USER);
}

process::process() {}

unsigned long process::call(void) {
    char entering_message[] = "entering process \0";
    log(entering_message);
    log(this->id);
    asm("hlt; cli");
    this->load();
    this->switch_on();
    disable_paging();
    // load_page_directory(this->page_dir);

    
    unsigned long result = call_process(address, this->args.args, this->args.size);

    char exit_message[] = "exiting process \0";
    log(exit_message);
    log(this->id);



    return result;
}

void process::load() {
    unsigned short flags = READ_WRITE | PRESENT;
    page_directory_t * kernel_page_directory = get_kernel_page_dir();
    unsigned long address = get_page(*kernel_page_directory, 0x400000, flags);
    get_page(*kernel_page_directory, 0x401000, flags);

    unsigned long mod_size =  module.mod_end - module.mod_start;
    memcopy(module.mod_start, address, mod_size / 4); 

    unsigned long loader_size = ((unsigned long)&loader_func - (unsigned long)&loader_func_end);
    memcopy((unsigned long)&loader_func, address + mod_size, loader_size/4 );

    this->address = (void *)(address + mod_size);
    this->physcal_start = address;
    this->physcal_end = address + mod_size + loader_size;
}

void process::switch_on() {
    page_directory_t * kernel_page_directory = get_kernel_page_dir();
    switch_page(physcal_start, *kernel_page_directory, 0, this->page_dir);
}

