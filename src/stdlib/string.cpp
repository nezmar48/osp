#include "../output/frame_buffer.h"

void hex_to_char_array_32(unsigned long hexValue, char result[]) {
    const char hexDigits[] = "0123456789ABCDEF";

    for(int i = 7; i >= 0; i--) {
        result[i] = hexDigits[hexValue % 16];  // Get the last hex digit
        hexValue /= 16;  // Move to the next digit
    }
}

void fb_write_hex_32(unsigned long hexValue) {
    char result[8];

    hex_to_char_array_32(hexValue, result);
    fb_write(result,sizeof(result),LIGHT_GREEN,BLACK);
}
