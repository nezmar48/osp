#ifndef PROCESS
#define PROCESS

#include "paging.h"
#include "multiboot.h"

extern "C" unsigned long call_process(page_directory_t * page_directory, unsigned long entry_symbol_ofset, unsigned long * args, unsigned long size);
extern "C" unsigned long return_process(unsigned long result);
class process {
    public: 

        process(multiboot_module_t *module);
        unsigned long address;

        struct {
            int size = 0;
            unsigned long * args;
        }args;

        multiboot_module_t module;
        unsigned long call(void);
        int id;
        page_directory_t * page_dir;
    private:
        static int ids;
        page_table_t * page_table_main;
        int main_table_kernel_index;
        page_table_t * page_table_stack;
        void load();
        void switch_on();
};

typedef struct{
    unsigned long eip;
    unsigned long ebp;
    unsigned long esp;
    unsigned long cr3;
}return_registers_t;

extern "C" return_registers_t return_registers;
extern process * current_process_pt;

#endif //PROCESS
