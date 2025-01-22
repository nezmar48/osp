#include "../multiboot.h"

const multiboot_uint32_t MULTIBOOT_FLAGS = MULTIBOOT_PAGE_ALIGN;

const multiboot_uint32_t CHECKSUM = - (MULTIBOOT_HEADER_MAGIC + MULTIBOOT_FLAGS);

__attribute__((section(".multiboot"), aligned(MULTIBOOT_PAGE_ALIGN)))
const struct multiboot_header mb_header = {
    .magic = MULTIBOOT_HEADER_MAGIC,
    .flags = MULTIBOOT_FLAGS,
    .checksum = CHECKSUM,
    .header_addr = 0,     
    .load_addr = 0,      
    .load_end_addr = 0, 
    .bss_end_addr = 0, 
    .entry_addr = 0,        
    .mode_type = 0, 
    .width = 0,      
    .height = 0,      
    .depth = 0         
};
