#ifndef INTERRUPTS
#define INTERRUPTS

class __attribute__((packed)) idt_entry {
    public:
        unsigned short isr_low;      // The lower 16 bits of the ISR's address
	    unsigned short kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	    unsigned char  reserved;     // Set to zero
	    unsigned char  attributes;   // Type and attributes; see the IDT page
	    unsigned short isr_high;     // The higher 16 bits of the ISR's address
};
class __attribute__((packed)) idtr{
    public:
	    unsigned short limit;
        unsigned long	base;
};

void idt_set_descriptor(unsigned char vector, void* isr, unsigned char flags);
unsigned long idt_init(void);



extern void* isr_stub_table[];

#endif // !INTERRUPTS
