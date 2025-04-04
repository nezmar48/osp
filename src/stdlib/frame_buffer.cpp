#include "../io.h"
#include "../std.h"

static short fb_pos = 0; // Track fb position persistently

void write(const char * char_pt, unsigned char fg, unsigned char bg) {
    for (unsigned short i = 0; char_pt[i] != '\0'; i++) {
        if (fb_pos > SCREEN_ROWS * SCREEN_WIDTH * 2 - 1)
            line_up();
        if (char_pt[i] == '\n') {
            fb_pos = (((fb_pos/2) / SCREEN_WIDTH + 1) * SCREEN_WIDTH * 2); // Move to next line
        } else {
            fb_write_cell(fb_pos, char_pt[i], fg, bg);
            fb_pos += 2;
        }
    }
    fb_move_cursor(fb_pos / 2); // Update fb position after writing
}
void write(const String &str, unsigned char fg, unsigned char bg) {
    write(str.c_str(), fg, bg);
}

void write(const unsigned long num, unsigned char fg, unsigned char bg) {
    write(String(num), fg, bg);
}

void write(const char ch, unsigned char fg, unsigned char bg) {
    char arr[2] = {ch, 0};
    write(arr, fg, bg);
}

void line_up(unsigned char num) {
    for (int i = 0; i < SCREEN_WIDTH * 2 * (SCREEN_ROWS - num) + 1; i ++) {
        fb_physical[i] = fb_physical[SCREEN_WIDTH * 2 * num + i];
    }
    for (int i = 0; i < SCREEN_WIDTH * 2 *  num; i ++) {
        fb_physical[SCREEN_WIDTH * 2 * (SCREEN_ROWS - num) + i] = 0;
    }
    fb_pos -= SCREEN_WIDTH * 2 * num; 
    if (fb_pos < 0)
        fb_pos = 0;
    fb_move_cursor(fb_pos / 2);
}

void clear_screen() {
    line_up(SCREEN_ROWS);
}
