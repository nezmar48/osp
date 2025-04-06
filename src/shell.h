#include "std.h"
#include "process.h"

void shell_main();
void quit(String* args, int count);

typedef void(*comeand_func_t)(String* args, int count);
typedef struct {
    bool is_func;
    comeand_func_t func;
    process proc;
}command;

Dictionary<command> * init_shell();
