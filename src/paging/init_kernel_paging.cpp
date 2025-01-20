#include "paging.h"
#include "../std.h"
extern "C" void loadPageDirectory(unsigned long*);
extern "C" void enablePaging();

page_directory_t kernel_page_directory;
page_table_t first_page_table;

extern "C" void init_kernel_paging() {

    init_page_directory(kernel_page_directory);
    init_memory_map();

    unsigned short flags = READ_WRITE | PRESENT; 

    kernel_page_directory[0] = ((unsigned long)first_page_table) | flags;

    // identity map first 4 Mb of memory
    for(unsigned int i = 0; i < 1024; i++) {
        get_page(kernel_page_directory, i * 0x1000, flags); //present read, write
        if (first_page_table[i] != ((i * 0x1000) | 3))
            asm ("cli; hlt; mov %0, %%eax" : : "r" (i));
    }

    loadPageDirectory(kernel_page_directory);
    enablePaging();
}
