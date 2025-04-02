#pragma clang diagnostic ignored "-Wexcessive-regsave"

#include "../std.h"
#include "../interrupts.h"
#include "../process.h"
#include "../paging.h"
#include "../io.h"


void pass_no_error_stub(default_interrupt_frame frame) { 
    char message[] = "no err int recieved";
    log(message);
    log(frame.code);
}

void pass_error_stub(error_interrupt_frame frame) {
    char message[] = "int recieved:";
    log(message);
    log(frame.code);
    log(frame.error);
}

void PIC_stub(default_interrupt_frame frame) {
    if (frame.code != 0x20 && frame.code != 0x21) {
        log("PIC interrupt recieved: ");
        log(frame.code);
    }
    switch (frame.code) {
        case 0x21:
            keyboard_handler();
            break;
        default:
            break;
    } 
    if (frame.code > PIC1_END_INTERRUPT)
        outb(PIC2_PORT_A, PIC_ACK);
    outb(PIC1_PORT_A, PIC_ACK);
}
void page_fault(error_interrupt_frame frame) {
    char msg[] = "page fault";
    log(msg);
    if (!(frame.error & 0x1)) { //non present page
        unsigned long virtual_address;
        asm ("mov %%cr2, %0" : "=r" (virtual_address));
        get_page(current_process_pt->page_dir, virtual_address, PRESENT | USER | READ_WRITE);
    }
    else {
        asm volatile ("cli; hlt; mov $0xdeadc0de, %eax");
    }
}

extern "C" void test_interrupt(default_interrupt_frame frame) {
    (void)frame;
    char message[] = "interrupts running";
    log(message);
    // log(frame.edi);
    // log(frame.esi);
    // log(frame.ebp);
    // log(frame.esp);
    // log(frame.ebx);
    // log(frame.edx);
    // log(frame.ecx);
    // log(frame.eax);
    // log(frame.eip);
    // log(frame.cs);
    // log(frame.flags);

}

extern "C" void system_call(default_interrupt_frame frame, unsigned long result) {
    (void)frame;
    char message[] = "system call recived";
    log(message);
    log(result);


    return_process(result);
}
