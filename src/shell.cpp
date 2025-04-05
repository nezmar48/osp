#include "std.h"
extern void shell_main() {
    clear_screen();
    String str = String();
    do {
        write("shell: \0");
        str = read_line_loud();
        // log(str);
    } while (str !=String("QUIT\n\0"));
    write("Quit called \n\0");
}
