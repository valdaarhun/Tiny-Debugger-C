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

void breakpointTracee(intptr_t addr){
    uint32_t word = Ptrace(PTRACE_PEEKTEXT, tracee.pid, (void *)addr, NULL);
    uint8_t byte = word & 0xff;
    printf("Word: %x\n", byte);
    uint32_t new_word = (word & ~0xff) | 0xcc;
    Ptrace(PTRACE_POKETEXT, tracee.pid, (void *)addr, (void *)(uint64_t)new_word);
    Breakpoint *h = createHashTableElement(addr);
    insertHashTableElement(h);
}

void continueTracee(){
    Ptrace(PTRACE_CONT, tracee.pid, NULL, NULL);
    int wstatus;
    waitpid(tracee.pid, &wstatus, 0);
}