#ifndef PROCESS
#define PROCESS

#include "paging.h"
#include "multiboot.h"

extern "C" unsigned long call_process(unsigned long * page_directory, unsigned long entry_symbol_ofset, unsigned long * args, unsigned long size);
extern "C" unsigned long return_process(unsigned long result);
class process {
    public: 

        process(multiboot_module_t *module, page_directory_t *page_directory, page_table_t *main_table, page_table_t *stack_table);
        unsigned long address;

        struct {
            int size = 0;
            unsigned long * args;
        }args;

        multiboot_module_t module;
        unsigned long call(void);
        int id;
    private:
        static int ids;
        unsigned long * page_dir;
        unsigned long * page_table_main;
        int main_table_kernel_index;
        unsigned long * page_table_stack;
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

#endif //PROCESS
