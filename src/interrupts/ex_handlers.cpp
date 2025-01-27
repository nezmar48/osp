#pragma clang diagnostic ignored "-Wexcessive-regsave"

#include "../std.h"
#include "../interrupts.h"
#include "../process.h"
#include "../paging.h"


void pass_no_error_stub(default_interrupt_frame * frame) { 
    (void)frame;
    char message[] = "no err int recived";
    log(message);
}

void pass_error_stub(default_interrupt_frame * frame, unsigned long error_code) {
    (void)frame;
    char message[] = "int recived:";
    log(message);
    log(error_code);
}

void page_fault(default_interrupt_frame * frame, unsigned long error_code) {
    (void)frame;
    log(error_code);
    asm volatile ("cli; hlt; mov $0xdeadc0de, %eax");
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
