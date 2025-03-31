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

class String {
private:
    char* data;
    unsigned short length;

public:
    String();
    String(const char* str);
    String(const String& other);
    String(unsigned long hex);
    ~String();

    String& operator=(const String& other);
    String operator+(const String& other) const;

    unsigned short size() const;
    const char* c_str() const;
};


#define SCREEN_WIDTH 80

class frame_buffer{
public:
    void write(const String& str, unsigned char fg = 0x0F, unsigned char bg = 0x00);
};
#endif //STD_LIB

