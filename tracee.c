#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "tracee.h"
#include "wrappers.h"

extern TraceeInfo tracee;

void killTracee(){
    kill(tracee.pid, SIGKILL);
}

void breakpointTracee(intptr_t addr){
    u_int32_t word = Ptrace(PTRACE_PEEKTEXT, tracee.pid, (void *)addr, NULL);
    word &= 0xff;
    printf("Word: %x\n", word);
}

void continueTracee(){
    Ptrace(PTRACE_CONT, tracee.pid, /* ignored */ NULL, NULL);
    int wstatus;
    waitpid(tracee.pid, &wstatus, 0);
}