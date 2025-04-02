#include "../std.h"
#include "../output.h"

void hex_to_char_array_32(unsigned long hexValue, char result[]) {
    const char hexDigits[] = "0123456789ABCDEF";

    for(int i = 7; i >= 0; i--) {
        result[i] = hexDigits[hexValue % 16];  // Get the last hex digit
        hexValue /= 16;  // Move to the next digit
    }
}

void serial_write_hex_32(unsigned long hexValue) {
    char result[8];

    hex_to_char_array_32(hexValue, result);
    serial_write(SERIAL_COM1_BASE, result, sizeof(result));
}

void log(const char * char_pt) {
    if(configured_com != SERIAL_COM1_BASE)
        serial_configure(SERIAL_COM1_BASE, Baud_115200);

    for (int i = 0; char_pt[i] != '\0'; i++)
        serial_write_byte(SERIAL_COM1_BASE, char_pt[i]);

    serial_write_byte(SERIAL_COM1_BASE, '\n');
}

void log(String &string) {
    log((char*)string.c_str()); 
}

void log(unsigned long hex) {
    char message[9];
    hex_to_char_array_32(hex, message);
    message[8] = '\0';
    log(message);
}
