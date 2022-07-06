#ifndef WRAPPERS_H_
#define WRAPPERS_H_

#include <sys/types.h>

void print_error();
pid_t Fork();
long Ptrace(enum __ptrace_request , pid_t , void *, void *);

#endif