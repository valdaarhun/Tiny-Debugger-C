#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/personality.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "tracee.h"
#include "userInput.h"
#include "wrappers.h"

TraceeInfo tracee;

void debug(){
    printf("Starting debugging process...\n");
    int wstatus;
    waitpid(tracee.pid, &wstatus, 0);
    printf("status: %d\n", WIFSTOPPED(wstatus));
    userInput();
}

int main(int argc, char *argv[]){
    if (argc != 2){
        fprintf(stderr, "USAGE: test [executable]\n");
        exit(1);
    }

    pid_t pid = Fork();

    if (pid == 0){
        char *argv_child[] = {argv[1], NULL};
        Personality(ADDR_NO_RANDOMIZE);
        /* pid, addr, data are ignored when using PTRACE_TRACEME */
        Ptrace(PTRACE_TRACEME, /* pid */ 0, /* addr */ NULL, /* data */ NULL);
        execv(argv[1], argv_child);

        /* If exec fails... */
        print_error("Failed to launch tracee program");
    }

    /* Parent process */
    tracee.pid = pid;
    debug();
}