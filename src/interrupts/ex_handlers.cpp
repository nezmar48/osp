#pragma clang diagnostic ignored "-Wexcessive-regsave"

#include "../std.h"
#include "../interrupts.h"

void default_no_error_stub(default_interrupt_frame * frame) {
    (void)frame;
     asm volatile ("cli; hlt; mov $0xdeadbeef, %eax");
}
void default_error_stub(default_interrupt_frame * frame, unsigned long error_code) {
    (void)frame;
    log(error_code);
    asm volatile ("cli; hlt; mov $0xdeadbeef, %eax");
}
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
void test_interrupt(default_interrupt_frame * frame) {
    (void)frame;
    char message[] = "interrupts running";
    log(message);
}
void system_call(default_interrupt_frame * frame, unsigned long error_code) {
    (void)frame;
    char message[] = "system call recived";
    log(message);
    log(error_code);
}
