#include "exec.h"
#define _BSD_SOURCE || _POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600

// sets the "key" argument with the key part of
// the "arg" argument and null-terminates it
static void get_environ_key(char* arg, char* key) {

    int i;
    for (i = 0; arg[i] != '='; i++)
        key[i] = arg[i];

    key[i] = END_STRING;
}

// sets the "value" argument with the value part of
// the "arg" argument and null-terminates it
static void get_environ_value(char* arg, char* value, int idx) {

    int i, j;
    for (i = (idx + 1), j = 0; i < strlen(arg); i++, j++)
        value[j] = arg[i];

    value[j] = END_STRING;
}

// sets the environment variables passed
// in the command line
//
// Hints:
// - use 'block_contains()' to
//  get the index where the '=' is
// - 'get_environ_*()' can be useful here
static void set_environ_vars(char** eargv, int eargc) {
    for(int i = 0; i < eargc; i++){
        int idx = block_contains(eargv[i], '=');
        char* value = &eargv[i][idx+1];
        eargv[i][idx] = '\0';

        if((setenv(eargv[i], value, 0)) == -1){
            perror("Error when setting env: ");
        }
    }
} 

// opens the file in which the stdin/stdout or
// stderr flow will be redirected, and returns
// the file descriptor
// 
// Find out what permissions it needs.
// Does it have to be closed after the execve(2) call?
//
// Hints:
// - if O_CREAT is used, add S_IWUSR and S_IRUSR
//  to make it a readable normal file
static int open_redir_fd(char* file) {

    // Your code here
    return -1;
}

// executes a command - does not return
//
// Hint:
// - check how the 'cmd' structs are defined
//  in types.h
void exec_cmd(struct cmd* cmd) {
struct execcmd* full_cmd = (struct execcmd*) cmd;
set_environ_vars(full_cmd->eargv, full_cmd->eargc);

    switch (cmd->type) {

        case EXEC:{
            // spawns a command
            if(full_cmd->argv[0] == NULL){
                exit(0);
            }
            if((execvp(full_cmd->argv[0], full_cmd->argv)) == -1){
                perror("Error with execvp: ");
            }
            _exit(0);
            break;
        }

        case BACK: {
            // runs a command in background
            if((execvp(full_cmd->argv[0], full_cmd->argv)) == -1){
                perror("Error with execvp: ");
            }
    
            break;
        }

        case REDIR: {
            // changes the input/output/stderr flow
            //
            // Your code here
            printf("Redirections are not yet implemented\n");
            _exit(-1);
            break;
        }
        
        case PIPE: {
            // pipes two commands
            //
            // Your code here
            printf("Pipes are not yet implemented\n");
                
            // free the memory allocated
            // for the pipe tree structure
            free_command(parsed_pipe);

            break;
        }
    }
}

