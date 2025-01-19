#ifndef PAGING_H
#define PAGING_H

// Function to initialize a page directory
// @param page_directory: Pointer to the page directory to be initialized
// @return: Pointer to the initialized page directory

typedef unsigned long page_table_t[1024] __attribute__((aligned(0x1000)));

typedef unsigned long page_directory_t[1024] __attribute__((aligned(0x1000)));

//table and directory flags
#define PRESENT 0x1
#define READ_WRITE 0x2
#define USER 0x4 //if not defined than superuser


void init_memory_map();
void init_page_directory(page_directory_t page_directory);

unsigned long get_page(page_directory_t directory, unsigned long virtual_address, unsigned short flags);

unsigned long get_free_page();

#endif // PAGING_H
