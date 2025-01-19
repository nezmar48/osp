#include "../std.h"

extern "C" int test_exception_handler(){
    char message[] = "interrupts running";
    log(message);
   return 32;
}

extern "C" void  page_fault_handler() {
    int test = 0xcafebabe;
    test++;
     __asm__ volatile ("cli; hlt"); // Completely hangs the computer
    // __builtin_unreachable(); 
}

extern "C" void  unimplemented_interrupt() {
    char message[] = "int 8 recived";
    log(message);
}
