#include "../interrupts.h"

__attribute__((aligned(0x10))) 
static idt_entry idt[256]; // Create an array of IDT entries; aligned for performance

idtr idtr;

void idt_set_descriptor(unsigned char vector, void* isr, unsigned char flags) {
    idt_entry* descriptor = &idt[vector];

    descriptor->isr_low        = (unsigned long)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08; //kernel code selector in GDT
    descriptor->attributes     = flags;
    descriptor->isr_high       = (unsigned long)isr >> 16;
    descriptor->reserved       = 0;
}


unsigned long idt_init() {

    idtr.base = (unsigned long)&idt[0];
    idtr.limit = (unsigned short)sizeof(idt_entry) * 255;

    for (int vector = 0; vector < 256; vector++) 
        idt_set_descriptor(vector, (void*)&default_no_error_stub, 0xE); //not present interrupt
    
    //set up intel reserved interrupts
    for (int vector = 0; vector < 32; vector++) 
        idt_set_descriptor(vector, intel_stub_table[vector], 0x8F); //present trap ring 0

    //my own interrupts
    idt_set_descriptor(8, (void*)&pass_no_error_stub, 0x8F); //present trap ring 0 // incorrecty implemented hardware interrupt
    idt_set_descriptor(14, (void*)&page_fault, 0x8F); //present trap ring 0
    idt_set_descriptor(32, (void*)&test_interrupt, 0x8E); //present interrupt ring 0
    idt_set_descriptor(0x80, (void*)&system_call, 0x8E); //present interrupt ring 0

    return (unsigned long)&idtr;
}
