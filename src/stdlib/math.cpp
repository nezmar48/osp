#include "../std.h"

unsigned long log_two(unsigned long num) {
    int result = 0;
    for (; num > 1; num /= 2, result++);
    return result;
}
