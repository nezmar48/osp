#include "output/frame_buffer.h"
#include "output/serial_port.h"
#include "output/frame_buffer.h"

extern "C" int kmain(){
    //frame buffer test
    // max 14 characters
    char buffer[] = "12345678901234";
	    fb_write(buffer,sizeof(buffer),LIGHT_GREEN,BLACK);
     
    //serial test
    
    serial_configure(SERIAL_COM1_BASE, Baud_115200);
    char serial_buffer[] = "serial running";
    serial_write(SERIAL_COM1_BASE, serial_buffer, sizeof(serial_buffer));

    return 0xcafebabe;
}

