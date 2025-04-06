#include "../std.h"
#include "../io.h"
char read_key() {
    while(!new_key);
    new_key = false;
    char ret = buffer[buffer_pos];
    clear_buffer();
    return ret;
}
char read_key_loud() {
    char ret = read_key();
    write(ret);
    return ret;
}

String read_line() {
    while (buffer[buffer_pos] != '\n');
    buffer[buffer_pos] = 0;
    String ret = String(buffer);
    clear_buffer();
    return ret;
}

char buffer2[buffer_size];
int buffer2_pos;
String read_line_loud() {
    for (int i = 0; i < buffer_size; i ++) {
        buffer2[i] = 0;
    }
    buffer2_pos = -1;
    char ch;
    do {
        ch = read_key_loud();
        buffer2[++buffer2_pos] = ch;
    } while (ch != '\n');
    buffer2[buffer2_pos] = 0;
    return  String(buffer2);
}

