#include "output/frame_buffer.h"
#include "output/serial_port.h"
#include "output/frame_buffer.h"

extern "C" int kmain(){
    //frame buffer test
    // max 14 characters
    // at 15 (0) [0x00000010003e] 0008:000000000010003e (unk. ctxt): movdqa xmm0, xmmword ptr ds:[ebx-4232] ; 660f6f8378efffff
    // causes int 6
    // tis is called during the fb_write function call not during it's execution
    // at 14 char 
    // (0) [0x000000100040] 0008:0000000000100040 (unk. ctxt): mov dword ptr ss:[ebp-23], 0x34333231 ; c745e931323334

    char buffer[] = "123456789012345";
	    fb_write(buffer,sizeof(buffer),LIGHT_GREEN,BLACK);
     
    //serial test
    
    serial_configure(SERIAL_COM1_BASE, Baud_115200);
    char serial_buffer[] = "serial running";
    serial_write(SERIAL_COM1_BASE, serial_buffer, sizeof(serial_buffer));

    return 0xcafebabe;
}

