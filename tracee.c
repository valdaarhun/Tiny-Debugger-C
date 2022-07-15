#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "hashTable.h"
#include "tracee.h"
#include "wrappers.h"

extern TraceeInfo tracee;

void killTracee(){
    kill(tracee.pid, SIGKILL);
}

void addBreakpointTracee(intptr_t addr){
    int32_t word = Ptrace(PTRACE_PEEKTEXT, tracee.pid, (void *)addr, NULL);
    int8_t byte = word & 0xff;
    printf("Word: %hhx\n", byte);
    int32_t new_word = (word & ~0xff) | 0xcc;
    Ptrace(PTRACE_POKETEXT, tracee.pid, (void *)addr, (void *)(int64_t)new_word);
    insertBreakpoint(addr, byte);
}

void continueTracee(){
    Ptrace(PTRACE_CONT, tracee.pid, NULL, NULL);
    int wstatus;
    waitpid(tracee.pid, &wstatus, 0);
}