#include "paging.h"
#include "../std.h"
page_directory_t kernel_page_directory;
page_table_t first_page_table;

extern "C" void init_kernel_paging() {

    init_page_directory(kernel_page_directory, READ_WRITE);
    init_memory_map();

    unsigned short flags = READ_WRITE | PRESENT; 

    kernel_page_directory[0] = ((unsigned long)first_page_table) | flags;

    // identity map first 4 Mb of memory
    for(unsigned int i = 0; i < 1024; i++) {
        get_page(kernel_page_directory, i * 0x1000, flags); //present read, write
        if (first_page_table[i] != ((i * 0x1000) | 3))
            asm ("cli; hlt; mov %0, %%eax" : : "r" (i));
    }

    load_page_directory(kernel_page_directory);
    enable_paging();
}

page_directory_t* get_kernel_page_dir() {
    return &kernel_page_directory;
}
