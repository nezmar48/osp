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
    // log((unsigned long)kernel_page_directory);
    // log((unsigned long)first_page_table);
    // identity map first 4 Mb of memory
    for(unsigned int i = 0; i < 1024; i++) {
        get_page(kernel_page_directory, i * 0x1000, flags); //present read, write
    }
    unsigned long not_identity_mapped = 0;
    for(unsigned int i = 0; i < 1024; i++)
    {
         not_identity_mapped += first_page_table[i] != ((i * 0x1000) | 3); // attributes: supervisor level, read/write, present.
    }
    if (not_identity_mapped != 0)
        asm ("cli; hlt; mov $0xfc, %eax");
    
    // asm ("cli; hlt; mov $0xfb, %eax");
    loadPageDirectory(kernel_page_directory);
    enablePaging();
}
