#include "../std.h"
#include "../shell.h"

Dictionary<command> * commands_pt;

void populate_commands() {
    command c = {true, quit,  nullptr};
    commands_pt->add("QUIT\0", c);
}

Dictionary<command>* init_shell() {
    commands_pt = new Dictionary<command>(); 
    populate_commands();
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
            write("invalid command\n\0", RED);
            continue;
        }
        if (cmd->is_func)
            cmd->func(&split_str[1], count - 1);
        else {
            cmd->proc.args.size = count - 1; 
            cmd->proc.args.args = (unsigned long *)malloc(sizeof(unsigned long) * (count - 1));
            for(int i = 0; i < count - 1; i ++) {
                cmd->proc.args.args[i] = split_str[i + 1].to_number();
            } 
            unsigned long result = cmd->proc.call();
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
