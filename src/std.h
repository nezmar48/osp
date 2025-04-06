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
    String* split(unsigned short& count) const;
    unsigned long to_number() const;
};

/* Frame buffer supported color value */
#define BLACK        0x0
#define BLUE         0x1
#define GREEN        0x2
#define CYAN         0x3
#define RED          0x4
#define MAGENTA      0x5
#define BROWN        0x6
#define LIGHT_GREY   0x7
#define DARK_GREY    0x8
#define LIGHT_BLUE   0x9
#define LIGHT_GREEN  0xA
#define LIGHT_CYAN   0xB
#define LIGHT_RED    0xC
#define LIGHT_MAGENTA 0xD
#define YELLOW       0xE
#define WHITE        0xF

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

// Generic Entry structure
template <typename T>
struct Entry {
    String key;
    T value;
};

template <typename T>
class Dictionary {
protected:
    Entry<T>* data;
    int capacity;
    int size;

    void resize();

public:
    Dictionary();
    virtual ~Dictionary();

    void add(const String& key, const T& value);

    T* find(const String& key);
};

#endif //STD_LIB
