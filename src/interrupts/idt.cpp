#include "../interrupts.h"
#include "../io.h"

const int IDT_ENTRIES = 0x32;  // Declare the constant

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

void pic_remap() {
    outb(0x20, 0x11);  // Start PIC1 initialization
    outb(0xA0, 0x11);  // Start PIC2 initialization

    outb(0x21, 0x20);  // Remap master PIC (IRQ0) to 0x20
    outb(0xA1, 0x28);  // Remap slave PIC (IRQ8) to 0x28

    outb(0x21, 0x04);  // Tell master PIC that slave is at IRQ2 (bit 2)
    outb(0xA1, 0x02);  // Tell slave PIC its cascade identity (bit 1)

    outb(0x21, 0x01);  // Set PIC1 to 8086 mode
    outb(0xA1, 0x01);  // Set PIC2 to 8086 mode

    outb(0x21, 0x00);  // Enable all IRQs on PIC1
    outb(0xA1, 0x00);  // Enable all IRQs on PIC2
}

unsigned long idt_init() {
    idtr.base = (unsigned long)&idt[0];
    idtr.limit = (unsigned short)sizeof(idt_entry) * IDT_ENTRIES- 1;

    for (unsigned char vector = 0; vector < IDT_ENTRIES; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        vectors[vector] = true;
    }

    pic_remap();

    return (unsigned long)&idtr;
}
