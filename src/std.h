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
    unsigned short length;

public:
    char* data;
    String();
    String(const char* str);
    String(const String& other);
    String(unsigned long hex);
    ~String();

    String& operator=(const String& other);
    String operator+(const String& other) const;
    bool operator==(const String& other) const;
    bool operator!=(const String& other) const;
    unsigned short size() const;
    const char* c_str() const;
};

void write(const String& str, unsigned char fg = 0x0F, unsigned char bg = 0x00);
void write(const unsigned long num, unsigned char fg = 0x0F, unsigned char bg = 0x00);
void write(const char * char_pt, unsigned char fg = 0x0F, unsigned char bg = 0x00);
void write(const char ch, unsigned char fg = 0x0F, unsigned char bg = 0x00);
void line_up(unsigned char num = 1);
void clear_screen();

void log(const char * char_pt);
void log(const String& string);
void log(const unsigned long hex);

char read_key();
char read_key_loud();
String read_line();
String read_line_loud();
#endif //STD_LIB

