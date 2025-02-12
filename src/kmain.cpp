#include "output/frame_buffer.h"
#include "output/serial_port.h"
#include "output/frame_buffer.h"
#include "keyboard_input.h"

extern "C" int kmain(){
   
    //frame buffer test
    serial_configure(SERIAL_COM1_BASE, Baud_115200);

    unsigned char buffer[] = "hihihihihihihi";
	    fb_write(buffer,sizeof(buffer),LIGHT_GREEN,BLACK);
     
    //serial test
    
    //char serial_buffer[] = "serial running";
    //serial_write(SERIAL_COM1_BASE, serial_buffer, sizeof(serial_buffer));
    
    int cursor_position = 0;
    unsigned char display_log[] = "";
    char writen_char = 0x0; 

    while (true) {
      char c = keyboard_scan_code_to_ascii(keyboard_read_scan_code());
      if (c != writen_char and c !=  0x0) {
        if (c == 0x2) {
          display_log[0] = '\0';
          clear_screen();
        } else if (c == 0x1) {

        } else {
          addChar(display_log,c);
          cursor_position++;
        }

	      fb_write(display_log,strlen((char*)display_log),RED,BLACK);
        writen_char = c;
        
      }
}    return 0xcafebabe;
}
 
