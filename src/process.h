#ifndef PROCESS
#define PROCESS

#include "multiboot.h"
#include "paging/paging.h"

class process {
    public: 
        process(multiboot_module_t *module);
        void * adress;
        unsigned long size; //size in dwords

        struct {
            int size = 0;
            unsigned long * args;
        }args;

        multiboot_module_t module;
        unsigned long call(void);
        int id;
    private:
        static int ids;
        void load();
        void init_page_directory();
        page_directory_t page_directory;
        page_table_t page_tables[1];
        
};

#endif //PROCESS
