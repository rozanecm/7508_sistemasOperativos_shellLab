#include "builtin.h"

char* split_by_space(char* cmd){
    int i = 0;
    
    while(cmd[i] != ' ')
        ++i;

    cmd[i++] = '\0';
    
    while(cmd[i] == ' ')
        ++i;

    return &cmd[i];
}

// returns true if the 'exit' call
// should be performed
int exit_shell(char* cmd) {

    // Your code here

    return 0;
}

// returns true if "chdir" was performed
// this means that if 'cmd' contains:
// 	$ cd directory (change to 'directory')
// 	$ cd (change to HOME)
// it has to be executed and then return true
int cd(char* cmd) {
    /* lets assume no command name will take more than 100 bytes */
    char cmd_name[100];
    sscanf(cmd, "%s", cmd_name);

    if(strcmp(cmd_name, "cd") == 0) {
        char* args = split_by_space(cmd);

        if (strlen(args) > 0) {
            chdir(args);
        } else {
            chdir(getenv("HOME"));
        }

        char* current_path = get_current_dir_name();
        snprintf(promt, sizeof promt, "(%s)", current_path);
        free(current_path);
        return 1;
    }
    
    return 0;
}

// returns true if 'pwd' was invoked
// in the command line
int pwd(char* cmd) {

    // Your code here

    return 0;
}

