#ifndef PAGING_H
#define PAGING_H

#define KERNEL_OFFSET 0xc0000000

typedef unsigned long page_table_t[1024] __attribute__((aligned(0x1000)));
typedef unsigned long page_directory_t[1024] __attribute__((aligned(0x1000)));
//table and directory flags
#define PRESENT 0x1
#define READ_WRITE 0x2
#define USER 0x4 //if not defined than superuser

void init_memory_map();
void init_kernel_paging();
void init_page_directory(page_directory_t &page_directory, unsigned short flags);
void init_page_table(page_table_t &page_table, unsigned short flags);

typedef struct {
    int dir;
    int table;
}page_index;

unsigned long get_page(page_directory_t &directory, unsigned long virtual_address, unsigned short flags);
unsigned long get_free_page();
unsigned long * get_table(page_directory_t &directory, int index);
page_index get_index(unsigned long virtual_address);
void switch_page(unsigned long src_add, page_directory_t &src_dir, unsigned long dst_add, page_directory_t &dst_dir);
void clear_flags(page_directory_t &directory, page_index index);
void clear_flags(page_table_t &table, int index);

extern "C" page_directory_t kernel_page_directory;
extern "C" page_table_t kernel_page_table;

#endif // PAGING_H
