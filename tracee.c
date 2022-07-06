#include <stdlib.h>
#include <sys/ptrace.h>
#include <unistd.h>

#include "tracee.h"
#include "wrappers.h"

extern TraceeInfo tracee;

void continueTracee(){
    Ptrace(PTRACE_CONT, tracee.pid, /* ignored */ NULL, NULL);
    pause();
}