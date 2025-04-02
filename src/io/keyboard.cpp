#include "../io.h"
#include "../std.h"

void keyboard_init() {
    // Unmask keyboard interrupt (IRQ1) in PIC
    outb(0x21, inb(0x21) & ~0x02);

    // Reset and enable the keyboard
    outb(0x64, 0xAD);  // Disable keyboard
    outb(0x64, 0xAE);  // Enable keyboard interface
    outb(0x60, 0xF4);  // Enable keyboard scannin
    
}
char alphabeth[257] =
{
    '\0', '\x1B', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',  // 00-0E
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n',             // 0F-1C
    '\0', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`',                 // 1D-29
    '\0', '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', '\0',             // 2A-36
    '\0', '\0', ' ', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',     // 37-42
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',   // 43-4E
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',   // 4F-5A
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',   // 5B-66
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',   // 67-72
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',   // 73-7E
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'    // 7F-FF (Reserved/Extended)
};

char translate_from_scan_code(char code) {
    return alphabeth[(int)code];
}

frame_buffer fb;
void keyboard_handler() {
    unsigned char code = inb(KBD_DATA_PORT);
    char ascii[2];
    ascii[1] = 0;
    ascii[0] = translate_from_scan_code(code);
    if (ascii[0] != 0)
        fb.write(ascii);
}
