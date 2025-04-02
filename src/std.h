#ifndef STD_LIB
#define STD_LIB

extern "C" void memcopy(unsigned long origin, unsigned long destination, unsigned long size);

unsigned long log_two(unsigned long num);

void * malloc(int size, int allign = 1);
void free(void * address);
void init_heap(unsigned long heap_start_add, unsigned long heap_end_add);
extern bool malloc_configured;

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

class frame_buffer {
public:
    void write(const String& str, unsigned char fg = 0x0F, unsigned char bg = 0x00);
    void write(const unsigned long num, unsigned char fg = 0x0F, unsigned char bg = 0x00);
    void write(const char * char_pt, unsigned char fg = 0x0F, unsigned char bg = 0x00);
    void line_up(unsigned char num = 1);
    void clear();
};

void log(const char * char_pt);
void log(String string);
void log(unsigned long hex);

#endif //STD_LIB

