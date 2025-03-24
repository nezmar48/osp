#include "../paging.h"
#include "../std.h"

page_table_t kernel_heap_table;
int kernel_size = 1; //size of kernel / 0x400000 + 1 (how many tables it has)
int kernel_heap_size = 1;

void init_kernel_paging() {

    init_memory_map();

    kernel_page_directory[0] = 0;

    init_page_table(&kernel_heap_table, READ_WRITE);
    kernel_page_directory[KERNEL_OFFSET / 0x400000 + kernel_size] = (unsigned long)remove_offset(kernel_heap_table) | PRESENT | READ_WRITE;
    
    for (int i = 0; i < 1024; i++) {
        get_page(&kernel_page_directory, KERNEL_OFFSET + kernel_size * 0x400000 + i * 0x1000 , READ_WRITE | PRESENT);
    }

}

void init_page_directory(page_directory_t *page_directory, unsigned short flags) {
     
    int i;
    for(i = 0; i < 1024; i++)
    {
        (*page_directory)[i] = flags;
    }
    int index = get_index(KERNEL_OFFSET).dir;
    for (int i = 0; i < (kernel_size + kernel_heap_size); i++) {
        (*page_directory)[index + i] = (unsigned long)remove_offset(get_table(&kernel_page_directory, index + i)) | PRESENT | READ_WRITE;
    }
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
    char message[] = "kernel page directory full\0";
    log(message);
    asm ("cli; hlt");
    return -1;
}

unsigned long get_page(page_directory_t * directory, unsigned long virtual_address, unsigned short flags) {
    unsigned long adress = get_free_page();
    if (adress == 1) {
        char message[] = "memory full\0";
        log(message);
        asm ("cli; hlt");
    }
    
    page_index index = get_index(virtual_address); 

    page_table_t * table = get_table(directory, index.dir);
    // log(virtual_address);
    // log((unsigned long)table);
    if ((unsigned long)remove_offset(table) == 0) {
        char message[] = "table not initilazed\0";
        log(message);
        table = (page_table_t *)malloc(0x1000, 0x1000);
        // log((unsigned long)table); 
        init_page_table(table, READ_WRITE);

        (*directory)[index.dir] = (unsigned long)remove_offset(table) | flags;

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
