#include "../std.h"
#include "../shell.h"

Dictionary<command> * commands_pt;

Dictionary<command>* init_shell(multiboot_info_t * multiboot_info) {
    commands_pt = new Dictionary<command>(); 

    multiboot_module_t * program_mod = add_offset((multiboot_module_t *)multiboot_info->mods_addr);
    process* add = new process(program_mod);
    commands_pt->add("ADD\0", command(add));

    commands_pt->add("QUIT\0", command(quit));
    return commands_pt;
}

bool shell_main_loop = true;
void shell_main() {
    clear_screen();
    write("Welocme to OSP! \n\n\0", LIGHT_GREEN);
    String * split_str;
    while (shell_main_loop) {
        write("shell: \0", LIGHT_BLUE);
        unsigned short count;
        split_str = read_line_loud().split(count);
        command* cmd = commands_pt->find(split_str[0]);
        if (cmd == nullptr) {
            invalid_command();
            continue;
        }
        if (cmd->is_func)
            cmd->func(&split_str[1], count - 1);
        else {
            cmd->proc->args.size = count - 1; 
            cmd->proc->args.args = (unsigned long *)malloc(sizeof(unsigned long) * (count - 1));
            for(int i = 0; i < count - 1; i ++) {
                cmd->proc->args.args[i] = split_str[i + 1].to_number();
            } 
            unsigned long result = cmd->proc->call();
            write("Process resut: ");
            write(result);
            write('\n');
        }
    };
}

void quit(String* args, int count) {
    if (count != 0) {
        write("invalid argument at pos 0: ", RED);
        write(args[0], YELLOW);
        write('\n');
        return;
    }
    shell_main_loop = false;
    write("Quit called \n\0");
}

void invalid_command(String* args, int count) {
    (void)args;
    (void)count;
    write("invalid_command\n\0", RED);
}
