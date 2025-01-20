#include "std.h"
#include "process.h"
#include "paging/paging.h"


int process::ids = 0;

process::process(multiboot_module_t *module, page_directory_t &directory, page_table_t &page_table) {
    this->id = ids++; 
    this->module = *module;
    this->page_dir = &directory;
    this->page_table = &page_table;
    init_page_directory(directory, READ_WRITE | USER);
    init_page_table(page_table, READ_WRITE | USER);
    *(this->page_dir)[0] |= (unsigned long)(*(this->page_table)) | PRESENT;
}

unsigned long process::call(void) {
    load();
    log(1);
    switch_on();
    log((unsigned long)(*(this->page_dir))[0]);
    log((unsigned long)(*(this->page_table))[0]);

    char entering_message[] = "entering process \0";
    log(entering_message);
    log(this->id);
    loaded_loader_process call_process = (loaded_loader_process)this->address;
    
    unsigned long result = call_process(this->page_dir, 0, this->args.args, this->args.size);

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

    unsigned long mod_size =  this->module.mod_end - this->module.mod_start;
    memcopy(this->module.mod_start, address, mod_size / 4); 

    unsigned long loader_size = ((unsigned long)&loader_func_end) - (unsigned long)&loader_func;
    memcopy((unsigned long)&loader_func, address + mod_size, loader_size/4 );

    this->address = (address + mod_size);
    this->physical_start = address;
    this->physical_end = address + mod_size + loader_size;
}

void process::switch_on() {
    page_directory_t * kernel_page_directory = get_kernel_page_dir();

    switch_page(physical_start, *kernel_page_directory, 0, *this->page_dir); 
    clear_flags(*this->page_table, 0);
    *(this->page_table)[0] |= PRESENT | READ_WRITE | USER; 

    switch_page(physical_start, *kernel_page_directory, 0x1000, *this->page_dir);
    clear_flags(*this->page_table, 1);
    *(this->page_table)[1] |= PRESENT | READ_WRITE | USER; 
    
}
