#include "std.h"
extern void shell_main() {
    clear_screen();
    while (true) {
        write("shell: \0");
        log(read_line_loud());
    }
}
