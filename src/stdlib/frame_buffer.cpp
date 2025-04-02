#include "../io.h"
#include "../std.h"

static short fb_pos = 0; // Track fb position persistently
void frame_buffer::write(const String &str, unsigned char fg, unsigned char bg) {
    for (unsigned short i = 0; i < str.size(); i++) {
        if (str.c_str()[i] == '\n') {
            fb_pos = ((fb_pos / SCREEN_WIDTH + 1) * SCREEN_WIDTH) * 2; // Move to next line
        } else {
            fb_write_cell(fb_pos, str.c_str()[i], fg, bg);
            fb_pos += 2;
        }
        if (fb_pos > SCREEN_ROWS * SCREEN_WIDTH * 2)
            this->line_up();
    }
    fb_move_cursor(fb_pos / 2); // Update fb position after writing
}

void frame_buffer::write(const unsigned long num, unsigned char fg, unsigned char bg) {
    write(String(num), fg, bg);
}

void frame_buffer::line_up(unsigned char num) {
    for (int i = 0; i < SCREEN_WIDTH * 2 * (SCREEN_ROWS - num); i ++) {
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

void frame_buffer::write(const char * char_pt, unsigned char fg, unsigned char bg) {
    this->write(String(char_pt), fg, bg);
}

void frame_buffer::clear() {
    this->line_up(SCREEN_ROWS);
}


