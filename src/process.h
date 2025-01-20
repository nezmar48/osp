#ifndef PROCESS
#define PROCESS

#include "paging//paging.h"
#include "multiboot.h"

typedef unsigned long (*loaded_loader_process)(page_directory_t * page_directory, unsigned long entry_symbol_ofset, unsigned long * args, unsigned long size);
class process {
    public: 
        process(multiboot_module_t *module, page_directory_t &directory, page_table_t &table);
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
        page_directory_t * page_dir;
        page_table_t * page_table;
        void load();
        unsigned long physical_start;
        unsigned long physical_end;
        void switch_on();
};

#endif //PROCESS
