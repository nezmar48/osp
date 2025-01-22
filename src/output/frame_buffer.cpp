#include "../output.h"	

static char *fb = (char *)0x000B8000;

void fb_move_cursor(unsigned short pos) {
	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
	outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  	outb(FB_DATA_PORT, pos & 0x00FF);
}

void fb_write_cell(unsigned int i, char c, unsigned char bg, unsigned char fg) {
	fb[i] = c;
	fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

unsigned int last_position = 0;

void fb_write(char *buf, unsigned int len, unsigned char fg, unsigned char bg) {
    for (unsigned int i = 0; i < len; i++) {
        fb_write_cell(i * 2 + last_position, *(buf + i), fg, bg);
        fb_move_cursor(2);
    }
    last_position += len*2;
}
