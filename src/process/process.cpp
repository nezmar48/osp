#include "../std.h"
#include "../process.h"
#include "../paging.h"


process * current_process_pt;
return_registers_t return_registers;
int process::ids = 0;

process::process(multiboot_module_t *module) {

    this->id = ids++; 
    this->module = *module;
    this->page_dir = (page_directory_t*)malloc(0x1000, 0x1000);
    this->page_table_main = (page_table_t*)malloc(0x1000, 0x1000);
    this->page_table_stack = (page_table_t*)malloc(0x1000, 0x1000);
    init_page_directory(this->page_dir, READ_WRITE | USER);

    init_page_table(this->page_table_main, READ_WRITE | USER);
    this->main_table_kernel_index = load_table_to_kernel(this->page_table_main);
    (*this->page_dir)[0] |= (unsigned long)remove_offset(this->page_table_main) | PRESENT;

    init_page_table(this->page_table_stack, READ_WRITE | USER);
    (*this->page_dir)[get_index(KERNEL_OFFSET - 0x1000).dir] |= (unsigned long)remove_offset(this->page_table_stack) | PRESENT;
}

process::~process() {
    free(page_dir);
    free(page_table_main);
    free(page_table_stack);
}

unsigned long process::call(void) {

    load();

    current_process_pt = this;
    char entering_message[] = "entering process \0";
    log(entering_message);
    log(this->id);
   
    unsigned long result = call_process(remove_offset(this->page_dir), 0, this->args.args, this->args.size);

    char exit_message[] = "exiting process \0";
    log(exit_message);
    log(this->id);

    return result;
}
void process::load() {

    unsigned short flags = READ_WRITE | PRESENT | USER;

    get_page((page_directory_t*)this->page_dir, 0x0, flags);
    get_page((page_directory_t*)this->page_dir, KERNEL_OFFSET - 0x1000, flags);
    unsigned long mod_size =  this->module.mod_end - this->module.mod_start;
    memcopy(this->module.mod_start + KERNEL_OFFSET, get_kernel_address(main_table_kernel_index, 0), mod_size / 4); 
}
