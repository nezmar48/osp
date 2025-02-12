#ifndef INCLUDE_KEYBOARD_H
#define INCLUDE_KEYBOARD_H

#define KEYBOARD_MAX_ASCII 83 

unsigned char keyboard_read_scan_code(void);

unsigned char keyboard_scan_code_to_ascii(unsigned char);

void addChar(unsigned char *s, char c);

int strlen(const char *s);

#endif /* INCLUDE_KEYBOARD_H */

