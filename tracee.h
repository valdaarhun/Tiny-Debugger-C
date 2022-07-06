#ifndef TRACEE_H
#define TRACEE_H

#include <sys/types.h>

#include "tracee.h"

typedef struct{
    pid_t pid;
}TraceeInfo;

void killTracee();
void continueTracee();

#endif