#ifndef PROCESS
#define PROCESS

#include "multiboot.h"
#include "paging/paging.h"

class process {
    public: 
        process(multiboot_module_t *module);
        process();
        void * address;

        struct {
            int size = 0;
            unsigned long * args;
        }args;

        multiboot_module_t module;
        unsigned long call(void);
        int id;
    private:
        page_directory_t page_dir;
        page_table_t first_page_table;
        unsigned long physcal_start;
        unsigned long physcal_end;
        static int ids;
        void load();
        void switch_on();
};

#endif //PROCESS
