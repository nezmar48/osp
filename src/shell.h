#include "std.h"
#include "process.h"
#include "multiboot.h"

void shell_main();
void quit(String* args, int count);
void invalid_command(String* args = 0, int count = 0);

typedef void(*comand_func_t)(String* args, int count);
class command{
public:
    bool is_func;
    comand_func_t func;
    process* proc;
    command() : is_func{true}, func{invalid_command}, proc{nullptr}{}
    command(comand_func_t func) :  is_func{true}, func{func}, proc{nullptr}{}
    command(process * proc) :  is_func{false}, func{0}, proc{proc}{}
};

Dictionary<command> * init_shell(multiboot_info_t *multiboot);
