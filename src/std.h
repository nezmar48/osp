#ifndef STD_LIB
#define STD_LIB

extern "C" void memcopy(unsigned long origin, unsigned long destination, unsigned long size);

void hex_to_char_array_32(unsigned long hexValue, char result[]);
void fb_write_hex_32(unsigned long hexValue);
void serial_write_hex_32(unsigned long hexValue);
void log(char * string);
void log(unsigned long hex);
unsigned long log_two(unsigned long num);

void * malloc(int size, int allign = 1);
void free(void * address);
void init_heap(unsigned long heap_start_add, unsigned long heap_end_add);

void malloc_test();

#endif //STD_LIB
