#include "../output/frame_buffer.h"
#include "../output/frame_buffer.h"
extern "C"
void default_exception_handler(void);

void  default_exception_handler() {
    // __asm__ volatile ("cli; hlt"); // Completely hangs the computer
    // __builtin_unreachable(); 
}

extern "C" int test_exception_handler(){
    char buffer[] = "interrupt";
	    fb_write(buffer,sizeof(buffer),LIGHT_GREEN,BLACK);
   return 32;
}
