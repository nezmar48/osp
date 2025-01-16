#include "multiboot.h"

class process {
    public: 
        process(multiboot_module_t *module);
        void * adress;

        struct {
            int size = 0;
            unsigned long * args;
        }args;

        multiboot_module_t module;
        unsigned long call(void);
};

process::process(multiboot_module_t *module) {
    this->module = *module;
    this->adress = (void *)module->mod_start;
}

unsigned long process::call(void) {
    unsigned long result;
    asm volatile("pusha");
    for (int i = 0; i < this->args.size; i++)
        asm volatile("push %0" : : "r" (this->args.args[1]));
    asm volatile(
    "call %1"
    : "=a" (result)
    : "r" (this->adress)
    );
    return 0;
}
