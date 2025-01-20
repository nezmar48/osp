#include "std.h"
#include "process.h"

extern "C" unsigned long call_process(void * adress, unsigned long * args, unsigned long size);

int process::ids = 0;

process::process(multiboot_module_t *module) {
    this->id = ids++; 
    this->module = *module;
    this->adress = (void *)module->mod_start;
}

unsigned long process::call(void) {
    memcopy((void *)module.mod_start,(void *)(module.mod_start + 0x1000), (module.mod_end - module.mod_start ) / 4); 
    char entering_message[] = "entering process \0";
    log(entering_message);
    log(this->id);

    
    unsigned long result = call_process((void *)(this->module.mod_start + 0x1000), this->args.args, this->args.size);

    char exit_message[] = "exiting process \0";
    log(exit_message);
    log(this->id);

    return result;
}
