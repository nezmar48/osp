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
    
    char entering_message[] = "entering process \0";
    log(entering_message);
    log(this->id);
    
    unsigned long result = call_process(this->adress, this->args.args, this->args.size);

    char exit_message[] = "exiting process \0";
    log(exit_message);
    log(this->id);

    return result;
}
