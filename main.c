#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "wrappers.h"

void user_input(pid_t pid){
    char buffer[256];
    while(1){
        fgets(buffer, 255, stdin);
        if (!strcmp("quit", buffer)){
            wait(NULL);
            exit(0);
        }
    }
}

void debug(pid_t pid){
    int wstatus;
    waitpid(pid, &wstatus, 0);
    printf("status: %d\n", wstatus);
    user_input(pid);
}

int main(int argc, char *argv[]){
    if (argc != 2){
        fprintf(stderr, "USAGE: test [executable]\n");
        exit(1);
    }

    pid_t pid = Fork();

    if (pid == 0){
        char *argv_child[] = {argv[1], NULL};
        execv(argv[1], argv_child);

        /* If exec fails... */
        print_error("Failed to launch tracee program\n");
    }
    debug(pid);
}