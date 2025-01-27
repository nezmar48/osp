#include "../paging.h"
#include "../std.h"
void init_kernel_paging() {

    init_memory_map();

    kernel_page_directory[0] = 0;

}
void init_page_directory(page_directory_t *page_directory, unsigned short flags) {
     
    int i;
    for(i = 0; i < 1024; i++)
    {
        (*page_directory)[i] = flags;
    }
    (*page_directory)[get_index(KERNEL_OFFSET).dir] = (unsigned long)remove_offset(kernel_page_table) | PRESENT | READ_WRITE;
}

void init_page_table(page_table_t *page_table, unsigned short flags) {
     
    int i;
    for(i = 0; i < 1024; i++)
    {
        (*page_table)[i] = flags;
    }
}
int load_table_to_kernel(page_table_t * table) {
    for (int i = 0; i < 1024; i++) {
        if ((kernel_page_directory[i] & 0xfffff000) == 0) {
            kernel_page_directory[i] = (unsigned long)remove_offset(table) | PRESENT | READ_WRITE;
            return i;
        }
    }
    char message[] = "kernel page directory full";
    log(message);
    asm ("cli; hlt");
    return -1;
}

unsigned long get_page(page_directory_t * directory, unsigned long virtual_address, unsigned short flags) {
    unsigned long adress = get_free_page();
    if (adress == 1) {
        char message[] = "memory full";
        log(message);
        asm ("cli; hlt");
    }
    
    page_index index = get_index(virtual_address); 

    page_table_t * table = get_table(directory, index.dir);

    if (table == 0) {
        char message[] = "table not initilazed";
        log(message);
        asm ("cli; hlt");
    }

    (*table)[index.table] = adress | flags; // present flags overwriten!!

    return adress;
}

unsigned long memory_map[1024 * 32];
unsigned long last_free = 0;

void init_memory_map() {
    for (int i = 0; i < 1024 * 32; i++)
        memory_map[i] = 0;

    for (int i = 0; i < 1024 / 32; i++) //kernel owns always firs 4 MB
        memory_map[i] --;
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

page_table_t * get_table(page_directory_t *directory, int index) {
    return add_offset((page_table_t *)((*directory)[index] & 0xfffff000));
}

unsigned long get_kernel_address(int kernel_index, unsigned long virtual_address) {
    int table_index = get_index(virtual_address).table;
    return kernel_index * 0x400000 + table_index * 0x1000;
}

void clear_flags(page_directory_t *directory, page_index index) {
    page_table_t * table = (page_table_t *)get_table(directory, index.dir);
    (*table)[index.table] &= 0xfffff000;
}

void clear_flags(page_table_t &table, int index) {
    table[index] &= 0xfffff000;
}
