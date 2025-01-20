#ifndef PROCESS
#define PROCESS

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
        int id;
    private:
        static int ids;
};

#endif //PROCESS
