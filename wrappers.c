#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
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