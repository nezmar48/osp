#include "paging.h"
#include "../std.h"

void init_page_directory(page_directory_t &page_directory, unsigned short flags) {
     
    int i;
    for(i = 0; i < 1024; i++)
    {
        page_directory[i] = flags;
    }

}

void init_page_table(page_table_t &page_table, unsigned short flags) {
     
    int i;
    for(i = 0; i < 1024; i++)
    {
        page_table[i] = flags;
    }

}

unsigned long get_page(page_directory_t &directory, unsigned long virtual_address, unsigned short flags) {
    
    unsigned long adress = get_free_page();
    if (adress == 1)
        asm ("cli; hlt; mov $0xff, %eax"); //memory full
    
    page_index index = get_index(virtual_address); 
    unsigned long * table = get_table(directory, index.dir);
    if (table == 0)
        asm ("cli; hlt; mov $0xfd, %eax"); //table not initilazed
    table[index.table] = adress | flags; // present flags overwriten!!
    return adress;
}

unsigned long memory_map[1024 * 32];
unsigned long last_free = 0;

void init_memory_map() {
    for (int i = 0; i < 1024 * 32; i++)
        memory_map[i] = 0;
}

unsigned long get_free_page(){
    unsigned long j = 1;
    unsigned long i = last_free;
    while ((j & memory_map[i]) != 0) {
        j <<= 1;
        if (j == 0) {
            j = 1;
            i++;
            if (i >= 1024 * 32)
                return 1;
        }
    }
    memory_map[i] = memory_map[i] | j;
    last_free = i;
    return ((i * 32) + log_two(j)) * 0x1000;

}

page_index get_index(unsigned long virtual_address) {
    page_index index;
    index.dir = virtual_address / 0x400000;
    index.table =  (virtual_address & 0x3ff000)/0x1000;
    return index;
}

unsigned long * get_table(page_directory_t &directory, int index) {
    return (unsigned long *)(directory[index] & 0xfffff000);
}

void switch_page(unsigned long src_add, page_directory_t &src_dir, unsigned long dst_add, page_directory_t &dst_dir) {
    page_index src_index = get_index(src_add);
    page_index dst_index = get_index(dst_add);
    unsigned long * src_table = get_table(src_dir, src_index.dir);
    unsigned long * dst_table = get_table(dst_dir, dst_index.dir);
    dst_table[dst_index.table] = src_table[src_index.table];
}
