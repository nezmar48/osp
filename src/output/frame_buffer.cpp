#include "frame_buffer.h"	

static char *fb = (char *)0x000B8000;

void fb_move_cursor(unsigned short pos) {
	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
	outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  outb(FB_DATA_PORT, pos & 0x00FF);
}

/** fb_write_cell:
     *  Writes a character with the given foreground and background to position i
     *  in the framebuffer.
     *
     *  @param i  The location in the framebuffer
     *  @param c  The character
     *  @param fg The foreground color
     *  @param bg The background color
     */

void fb_write_cell(unsigned int i, char c, unsigned char bg, unsigned char fg) {
	fb[i] = c;
	fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define FB_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT * 2)

int fb_write(unsigned char *buf, unsigned int len, unsigned char fg, unsigned char bg){
    	   unsigned int i;
    for (i = 0; i < len && i < (SCREEN_WIDTH * SCREEN_HEIGHT); i++) {
        unsigned int row = i / SCREEN_WIDTH;  // Calculate row number
        unsigned int col = i % SCREEN_WIDTH;  // Calculate column number
        unsigned int pos = (row * SCREEN_WIDTH + col) * 2;  // Position in framebuffer
        fb_write_cell(pos, buf[i], fg, bg);
    }
    return i;
}

void clear_screen() {
    unsigned char cleaner_buffer[FB_SIZE + 1];  
    for (int i = 0; i < FB_SIZE; i++) {
        cleaner_buffer[i] = ' ';  
    }
    cleaner_buffer[FB_SIZE] = '\0';  

    fb_write(cleaner_buffer, FB_SIZE, LIGHT_GREEN, BLACK);
}
