#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/personality.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <unistd.h>

#include "tracee.h"
#include "wrappers.h"

extern TraceeInfo tracee;

void print_error(char *msg){
    fprintf(stderr, "%s: %s (%d)\n", msg, strerror(errno), errno);
}

int Personality(unsigned long persona){
    int status = personality(persona);
    if (status < 0){
        print_error("Error setting personality");
        exit(1);
    }
    return status;
}

pid_t Fork(){
    pid_t pid = fork();
    if (pid < 0){
        print_error("Error with fork");
        exit(1);
    }
    return pid;
}

long Ptrace(enum __ptrace_request request, pid_t pid, void *addr, void *data){
    /* Reset errno since for some ptrace functions (eg: PTRACE_PEEKTEXT), ptrace might return a negative value in a successful operation */
    errno = 0;
    long status = ptrace(request, pid, addr, data);
    if (status < 0 && errno != 0){
        print_error("Error setting trace");
        kill(tracee.pid, SIGKILL);
        exit(1);
    }
    return status;
}