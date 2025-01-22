#ifndef PAGING_H
#define PAGING_H

typedef unsigned long page_table_t[1024] __attribute__((aligned(0x1000)));
typedef unsigned long page_directory_t[1024] __attribute__((aligned(0x1000)));
//table and directory flags
#define PRESENT 0x1
#define READ_WRITE 0x2
#define USER 0x4 //if not defined than superuser

void init_memory_map();
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

extern "C" void load_page_directory(page_directory_t &directory);
extern "C" void enable_paging();
extern "C" void disable_paging();

extern "C" unsigned long loader_func(page_directory_t * page_directory, unsigned long entry_symbol_ofset, unsigned long * args, unsigned long size);
extern "C" void loader_func_end(void);


page_directory_t* get_kernel_page_dir();

#endif // PAGING_H
