#include "../output.h"
#include "../std.h"

// Default constructor
String::String() : data(nullptr), length(0) {}

// Constructor from C-string
String::String(const char* str) {
    length = 0;
    while (str[length] != '\0') {
        length++;
    }
    data = (char *)malloc(length + 1);
    for (unsigned short i = 0; i < length; i++) {
        data[i] = str[i];
    }
    data[length] = '\0';
}

// Copy constructor
String::String(const String& other) {
    length = other.length;
    data = (char *)malloc(length + 1);
    for (unsigned short i = 0; i < length; i++) {
        data[i] = other.data[i];
    }
    data[length] = '\0';
}

//hex 
String::String(unsigned long hex) {
    const char hexDigits[] = "0123456789ABCDEF";

    length = 8;
    data = (char *)malloc(length + 1);
    data[length + 1] = '\0';
    for(int i = length; i > 0; i--) {
        data[i - 1] = hexDigits[hex% 16];  // Get the last hex digit
        hex /= 16;  // Move to the next digit
    }
}

// Destructor
String::~String() {
    free(data);
}

// Copy assignment operator
String& String::operator=(const String& other) {
    if (this != &other) {
        free(data);
        length = other.length;
        data = (char *)malloc(length + 1);
        for (unsigned short i = 0; i < length; i++) {
            data[i] = other.data[i];
        }
        data[length] = '\0';
    }
    return *this;
}

// Concatenation operator
String String::operator+(const String& other) const {
    String result;
    result.length = length + other.length;
    result.data = (char *)malloc(result.length + 1);
    for (unsigned short i = 0; i < length; i++) {
        result.data[i] = data[i];
    }
    for (unsigned short i = 0; i < other.length; i++) {
        result.data[length + i] = other.data[i];
    }
    result.data[result.length] = '\0';
    return result;
}

// Get the length of the string
unsigned short String::size() const {
    return length;
}

// Get the C-string representation
const char* String::c_str() const {
    return data;
}

void frame_buffer::write(const String& str, unsigned char fg, unsigned char bg) {
    static unsigned short cursor_pos = 0; // Track cursor position persistently
    for (unsigned short i = 0; i < str.size(); i++) {
        if (str.c_str()[i] == '\n') {
            cursor_pos = ((cursor_pos / SCREEN_WIDTH + 1) * SCREEN_WIDTH)*2; // Move to next line
        } else {
            fb_write_cell(cursor_pos, str.c_str()[i], fg, bg);
            cursor_pos += 2;
        }
    }
    fb_move_cursor(cursor_pos); // Update cursor position after writing
}

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

void serial_write_hex_32(unsigned long hexValue) {
    char result[8];

    hex_to_char_array_32(hexValue, result);
    serial_write(SERIAL_COM1_BASE, result, sizeof(result));
}

void log(char * string) {
    if(configured_com != SERIAL_COM1_BASE)
        serial_configure(SERIAL_COM1_BASE, Baud_115200);

    for (int i = 0; string[i] != '\0'; i++)
        serial_write_byte(SERIAL_COM1_BASE, string[i]);

    serial_write_byte(SERIAL_COM1_BASE, '\n');
}

void log(unsigned long hex) {

    char message[9];
    hex_to_char_array_32(hex, message);
    message[8] = '\0';

    log(message);
}
