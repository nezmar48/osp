#ifndef INCLUDE_FRAMEBUFFER_H
#define INCLUDE_FRAMEBUFFER_H

#pragma once
#include "io.h"

/* The I/O ports */
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15

/* Frame buffer supported color value */
#define BLACK        0x0
#define BLUE         0x1
#define GREEN        0x2
#define CYAN         0x3
#define RED          0x4
#define MAGENTA      0x5
#define BROWN        0x6
#define LIGHT_GREY   0x7
#define DARK_GREY    0x8
#define LIGHT_BLUE   0x9
#define LIGHT_GREEN  0xA
#define LIGHT_CYAN   0xB
#define LIGHT_RED    0xC
#define LIGHT_MAGENTA 0xD
#define YELLOW       0xE
#define WHITE        0xF

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos);

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);

/** write:
 *  writes the contents of the buffer buf of length len to the screen
 *
 *  @param buf  Buffer that has contents to be written to screen
 *  @param len  Length of buffer
 */

void fb_write(char *buf, unsigned int len, unsigned char fg, unsigned char bg);

#endif /* INCLUDE_IO_H */
