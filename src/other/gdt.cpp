#include "../gdt.h"
unsigned long long gdt[GDT_ENTRIES]; // Null, Kernel Code, Kernel Data, User Code, User Data
gdt_ptr gdt_ptr;

void create_descriptor(int entry, unsigned long base, unsigned long limit, unsigned short flag)
{
    unsigned long long descriptor;
 
    // Create the high 32 bit segment
    descriptor  =  limit       & 0x000F0000;         // set limit bits 19:16
    descriptor |= (flag <<  8) & 0x00F0FF00;         // set type, p, dpl, s, g, d/b, l and avl fields
    descriptor |= (base >> 16) & 0x000000FF;         // set base bits 23:16
    descriptor |=  base        & 0xFF000000;         // set base bits 31:24
 
    // Shift by 32 to allow for low part of segment
    descriptor <<= 32;
 
    // Create the low 32 bit segment
    descriptor |= base  << 16;                       // set base bits 15:0
    descriptor |= limit  & 0x0000FFFF;               // set limit bits 15:0 
    
    if(entry >= GDT_ENTRIES) return;

    gdt[entry] = descriptor;

}


unsigned long create_gdt(void)
{
    create_descriptor(0, 0, 0, 0);
    create_descriptor(1, 0, 0xFFFFFFFF, (GDT_CODE_PL0));
    create_descriptor(2, 0, 0xFFFFFFFF, (GDT_DATA_PL0));
    create_descriptor(3, 0, 0xFFFFFFFF, (GDT_CODE_PL3));
    create_descriptor(4, 0, 0xFFFFFFFF, (GDT_DATA_PL3));
    
    gdt_ptr.address = (unsigned long)&gdt;
    gdt_ptr.size = sizeof(gdt) - 1;
 
    return (unsigned long)&gdt_ptr;
}
