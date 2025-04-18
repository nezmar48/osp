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

typedef struct {
    unsigned long code;
    unsigned long edi;
    unsigned long esi;
    unsigned long ebp;
    unsigned long esp;
    unsigned long ebx;
    unsigned long edx;
    unsigned long ecx;
    unsigned long eax;
    unsigned long eip;
    unsigned long cs;
    unsigned long flags;
}default_interrupt_frame;

typedef struct {
    unsigned long code;
    unsigned long edi;
    unsigned long esi;
    unsigned long ebp;
    unsigned long esp;
    unsigned long ebx;
    unsigned long edx;
    unsigned long ecx;
    unsigned long eax;
    unsigned long error;
    unsigned long eip;
    unsigned long cs;
    unsigned long flags;
}error_interrupt_frame;

#define PIC1_START_INTERRUPT 0x20
#define PIC2_START_INTERRUPT 0x28
#define PIC1_END_INTERRUPT   PIC1_START_INTERRUPT + 7
#define PIC2_END_INTERRUPT   PIC2_START_INTERRUPT + 7

extern "C" void* isr_stub_table[];

extern "C" void pass_no_error_stub(default_interrupt_frame frame);
extern "C" void pass_error_stub(error_interrupt_frame frame);
extern "C" void PIC_stub(default_interrupt_frame frame); 
extern "C" void page_fault(error_interrupt_frame frame);
extern "C" void test_interrupt(default_interrupt_frame frame);
extern "C" void system_call(default_interrupt_frame frame, unsigned long result);

#endif // !INTERRUPTS
