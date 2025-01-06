#include "paging.h"
extern "C" void loadPageDirectory(unsigned long*);
extern "C" void enablePaging();

unsigned long kernel_page_directory[1024] __attribute__((aligned(4096)));
unsigned long first_page_table[1024] __attribute__((aligned(4096)));

extern "C" void init_kernel_paging() {

    init_page_directory(kernel_page_directory);
    
    // identity map first 4 Mb of memory
    for(unsigned int i = 0; i < 1024; i++)
    {
        first_page_table[i] = (i * 0x1000) | 3; // attributes: supervisor level, read/write, present.
    }

    kernel_page_directory[0] = ((unsigned long)first_page_table) | 3;

    loadPageDirectory(kernel_page_directory);
    enablePaging();
}
