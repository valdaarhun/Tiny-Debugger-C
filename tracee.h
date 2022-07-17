#ifndef TRACEE_H
#define TRACEE_H

#include <sys/types.h>

#include "tracee.h"

typedef struct{
    pid_t pid;
}TraceeInfo;

void killTracee();
void addBreakpointTracee(intptr_t);
void deleteBreakpointTracee(intptr_t);
void listBreakpointTracee();
void continueTracee();
void getRegValue(char *);
void getMemValue(intptr_t);

#endif