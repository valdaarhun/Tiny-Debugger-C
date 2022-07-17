#ifndef REGISTERS_H
#define REGISTERS_H

/* 
    Register names mapped to register numbers in accordance with the
    DWARF mapping described here: https://www.uclibc.org/docs/psABI-x86_64.pdf
*/
typedef enum{
    RAX,
    RDX,
    RCX,
    RBX,
    RSI,
    RDI,
    RBP,
    RSP,
    R8, R9, R10, R11, R12, R13, R14, R15,
    RFLAGS = 49,
    ES,
    CS,
    SS,
    DS,
    FS,
    GS,
    FS_BASE = 58,
    GS_BASE,
}Registers;

#endif