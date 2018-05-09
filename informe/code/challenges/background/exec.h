#ifndef EXEC_H
#define EXEC_H

#include "defs.h"
#include "types.h"
#include "utils.h"
#include "freecmd.h"

extern struct cmd* parsed_pipe;

extern pid_t background_process_pid;

void exec_cmd(struct cmd* c);

#endif // EXEC_H
