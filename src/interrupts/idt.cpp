#include "../interrupts.h"

const int IDT_ENTRIES = 34;  // Declare the constant

__attribute__((aligned(0x10))) 
static idt_entry idt[256]; // Create an array of IDT entries; aligned for performance

static idtr idtr;

static bool vectors[IDT_ENTRIES];
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
    idtr.limit = (unsigned short)sizeof(idt_entry) * IDT_ENTRIES- 1;

    for (unsigned char vector = 0; vector < IDT_ENTRIES; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        vectors[vector] = true;
    }

    return (unsigned long)&idtr;
}
