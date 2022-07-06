#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <unistd.h>

#include "wrappers.h"

void print_error(char *msg){
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
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
    long status = ptrace(request, pid, addr, data);
    if (status < 0){
        print_error("Error setting trace");
        exit(1);
    }
    return status;
}