#include "defs.h"
#include "types.h"
#include "readline.h"
#include "runcmd.h"

char promt[PRMTLEN] = {0};


static void handler(int signal, siginfo_t* s, void* u){
    if (s->si_pid == background_process_pid){ 
        if(signal == SIGCHLD) 
            printf("==> terminado: PID=%i\n", s->si_pid);
    }
}


// runs a shell command
static void run_shell() {

	char* cmd;

    struct sigaction act;
    act.sa_flags = SA_SIGINFO | SA_RESTART;
    act.sa_sigaction = handler;
    sigaction(SIGCHLD, &act, NULL);

	while ((cmd = read_line(promt)) != NULL)
		if (run_cmd(cmd) == EXIT_SHELL)
			return;
}

// initialize the shell
// with the "HOME" directory
static void init_shell() {
	char buf[BUFLEN] = {0};
	char* home = getenv("HOME");

	if (chdir(home) < 0) {
		snprintf(buf, sizeof buf, "cannot cd to %s ", home);
		perror(buf);
	} else {
		snprintf(promt, sizeof promt, "(%s)", home);
	}	
}

int main(void) {

	init_shell();

	run_shell();

	return 0;
}

