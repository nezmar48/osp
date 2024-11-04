#include "serial_port.cpp"
#include "frame_buffer.cpp"
/** fb_write_cell:
     *  Writes a character with the given foreground and background to position i
     *  in the framebuffer.
     *
     *  @param i  The location in the framebuffer
     *  @param c  The character
     *  @param fg The foreground color
     *  @param bg The background color
     */

extern "C" int kmain(){

  
      char buffer[] = "t'is wankers innit";
	    fb_write(buffer,sizeof(buffer));
       
      serial_configure(SERIAL_COM1_BASE, Baud_115200);
      serial_write(SERIAL_COM1_BASE, buffer, sizeof(buffer));

      fb_write_cell(0,'C',2,8);
      return 0xcafebabe;
}

