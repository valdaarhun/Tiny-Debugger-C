#include <stdlib.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <unistd.h>

#include "tracee.h"
#include "wrappers.h"

extern TraceeInfo tracee;

void killTracee(){
    kill(tracee.pid, SIGKILL);
}

void continueTracee(){
    Ptrace(PTRACE_CONT, tracee.pid, /* ignored */ NULL, NULL);
    pause();
}