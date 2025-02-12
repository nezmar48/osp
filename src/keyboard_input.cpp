#include "output/io.h"

#define KBD_DATA_PORT   0x60
  /** read_scan_code:
   *  Reads a scan code from the keyboard
   *
   *  @return The scan code (NOT an ASCII character!)
    */
unsigned char keyboard_read_scan_code(void)
{
    return inb(KBD_DATA_PORT);
};

unsigned char keyboard_scan_code_to_ascii(unsigned char scan_code)
{
	unsigned char ascii[256] =
	{
		0x0, 0x0, '1', '2', '3', '4', '5', '6',		// 0 - 7
		'7', '8', '9', '0', '-', '=', 0x1, 0x0,		// 8 - 15
		'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',		// 16 - 23
		'o', 'p', '[', ']', 0x2, 0x0, 'a', 's',	// 24 - 31
		'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',		// 32 - 39
		'\'', '`', 0x0, '\\', 'z', 'x', 'c', 'v',	// 40 - 47
		'b', 'n', 'm', ',', '.', '/', 0x0, '*',		// 48 - 55
		0x0, ' ', 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,		// 56 - 63
		0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, '7',		// 64 - 71
		'8', '9', '-', '4', '5', '6', '+', '1',		// 72 - 79
		'2', '3', '0', '.'				// 80 - 83
	};

	return ascii[scan_code];
}
void addChar(unsigned char *s, char c) {

    while (*s) s++;  

    // Append the new character
    *s = c;

    // Add null terminator at the new end
    *(s + 1) = '\0';  // Move pointer to the end
  
};

int strlen(const char *s) {
    int len = 0;
    while (*s++) len++;
    return len;
}
