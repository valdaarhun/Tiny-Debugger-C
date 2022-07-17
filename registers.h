#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>
#include <sys/user.h>

/* 
    Register names mapped to register numbers in accordance with the
    DWARF mapping described here: https://www.uclibc.org/docs/psABI-x86_64.pdf
    rip and orig_rax from the user_regs_struct (defined in <sys/user.h>) has also been included in the enum.
*/
typedef enum{
    RIP_T = -2,
    ORIG_RAX_T,
    RAX_T,
    RDX_T,
    RCX_T,
    RBX_T,
    RSI_T,
    RDI_T,
    RBP_T,
    RSP_T,
    R8_T, R9_T, R10_T, R11_T, R12_T, R13_T, R14_T, R15_T,
    RFLAGS_T = 49,
    ES_T,
    CS_T,
    SS_T,
    DS_T,
    FS_T,
    GS_T,
    FS_BASE_T = 58,
    GS_BASE_T,
}RegisterNumber;

typedef struct{
    RegisterNumber register_number;
    uint64_t value;
}RegisterInfo;

void writeToCache(struct user_regs_struct *);
uint64_t readFromCache(char *);

#endif