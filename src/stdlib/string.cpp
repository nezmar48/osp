#include "../std.h"

// Default constructor
String::String() {
    data = (char*) malloc(1);
    data[0] = 0;
    length = 0;
}

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

// Equality operator
bool String::operator==(const String& other) const {
    if (length != other.length) {
        return false;
    }
    for (unsigned short i = 0; i < length; i++) {
        log(this->data[i]);
        log(other.data[i]);
        if (data[i] != other.data[i]) {
            log("not same");
            return false;
        }
    }
    return true;
}

bool String::operator!=(const String& other) const {
    return !(*this == other);
}
