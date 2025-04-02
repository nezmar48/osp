#include "../output.h"	
#include "../paging.h"

static char *fb = (char *)(0x000B8000 + KERNEL_OFFSET) ;

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

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define FB_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT * 2)

void fb_write(unsigned char *buf, unsigned int len, unsigned char fg, unsigned char bg) {
    fb_write((char*)buf, len, fg, bg);
}


void fb_write(char *buf, unsigned int len, unsigned char fg, unsigned char bg){
    	   unsigned int i;
    for (i = 0; i < len && i < (SCREEN_WIDTH * SCREEN_HEIGHT); i++) {
        unsigned int row = i / SCREEN_WIDTH;  // Calculate row number
        unsigned int col = i % SCREEN_WIDTH;  // Calculate column number
        unsigned int pos = (row * SCREEN_WIDTH + col) * 2;  // Position in framebuffer
        fb_write_cell(pos, buf[i], fg, bg);
    }
    //return i;
}

void clear_screen() {
    unsigned char cleaner_buffer[FB_SIZE + 1];  
    for (int i = 0; i < FB_SIZE; i++) {
        cleaner_buffer[i] = ' ';  
    }
    cleaner_buffer[FB_SIZE] = '\0';  
    fb_write(cleaner_buffer, FB_SIZE, LIGHT_GREEN, BLACK);
}
/* unsigned int last_position = 0;

void fb_write(char *buf, unsigned int len, unsigned char fg, unsigned char bg) {
    for (unsigned int i = 0; i < len; i++) {
        fb_write_cell(i * 2 + last_position, *(buf + i), fg, bg);
        fb_move_cursor(2);
    }
    last_position += len*2;
} */
