#ifndef STD_LIB
#define STD_LIB

void hex_to_char_array_32(unsigned long hexValue, char result[]);
void fb_write_hex_32(unsigned long hexValue);
void serial_write_hex_32(unsigned long hexValue);
void log(char * string);
void log(unsigned long hex);

#endif //STD_LIB
