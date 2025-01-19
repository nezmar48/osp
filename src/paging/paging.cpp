#include "paging.h"
#include "../std.h"

void init_page_directory(page_directory_t page_directory) {
    //set each entry to not present
    int i;
    for(i = 0; i < 1024; i++)
    {
        // This sets the following flags to the pages:
        //   Supervisor: Only kernel-mode can access them
        //   Write Enabled: It can be both read from and written to
        //   Not Present: The page table is not present
        page_directory[i] = 0x00000002;
    }

}


unsigned long get_page(page_directory_t directory, unsigned long virtual_address, unsigned short flags) {
    
    unsigned long adress = get_free_page();
    if (adress == 1)
        asm ("cli; hlt; mov $0xff, %eax"); //memory full
    
    unsigned long directory_index = virtual_address / 0x400000;

    unsigned long * table = (unsigned long *)(directory[directory_index] & 0xfffff000);
    if (table == 0)
        asm ("cli; hlt; mov $0xfd, %eax"); //table not initilazed
    unsigned long table_index = (virtual_address & 0x3ff000)/0x1000;
    table[table_index] = adress | flags; // present flags overwriten!!
    return adress;
}

unsigned long memory_map[1024 * 32];

void init_memory_map() {

    for (int i = 0; i < 1024 * 32; i++)
        memory_map[i] = 0;
}

unsigned long get_free_page(){
    unsigned long j = 1;
    unsigned long i = 0;
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
    return ((i * 32) + log_two(j)) * 0x1000;
}
