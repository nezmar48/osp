#include "../output/serial_port.h"
extern "C"
void default_exception_handler(void);

void  default_exception_handler() {
     __asm__ volatile ("cli; hlt"); // Completely hangs the computer
    // __builtin_unreachable(); 
}

extern "C" int test_exception_handler(){

    serial_configure(SERIAL_COM1_BASE, Baud_115200);
    char serial_buffer[] = "interrupts running \n";
    serial_write(SERIAL_COM1_BASE, serial_buffer, sizeof(serial_buffer));
   return 32;
}

extern "C" void  page_fault_handler() {
    int test = 0xcafebabe;
    test++;
     __asm__ volatile ("cli; hlt"); // Completely hangs the computer
    // __builtin_unreachable(); 
}
