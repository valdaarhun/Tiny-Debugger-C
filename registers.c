#include <string.h>
#include <sys/user.h>

#include "registers.h"

#define REG_SET 27

RegisterInfo regs[REG_SET] = {
    {R15_T, 0},
    {R14_T, 0},
    {R13_T, 0},
    {R12_T, 0},
    {RBP_T, 0},
    {RBX_T, 0},
    {R11_T, 0},
    {R10_T, 0},
    {R9_T, 0},
    {R8_T, 0},
    {RAX_T, 0},
    {RCX_T, 0},
    {RDX_T, 0},
    {RSI_T, 0},
    {RDI_T, 0},
    {ORIG_RAX_T, 0},
    {RIP_T, 0},
    {CS_T, 0},
    {RFLAGS_T, 0},
    {RSP_T, 0},
    {SS_T, 0},
    {FS_BASE_T, 0},
    {GS_BASE_T, 0},
    {DS_T, 0},
    {ES_T, 0},
    {FS_T, 0},
    {GS_T, 0}
};

static RegisterNumber getRegNumFromRegName(char *reg){
    char *register_names[] = {
        "r15", "r14", "r13", "r12", "rbp", "rbx", "r11", "r10", "r9",
        "r8", "rax", "rcx", "rdx", "rsi", "rdi", "orig_rax", "rip", "cs",
        "eflags", "rsp", "ss", "fs_base", "gs_base", "ds", "es", "fs", "gs"
    };
    RegisterNumber register_numbers[] = {
        R15_T, R14_T, R13_T, R12_T, RBP_T, RBX_T, R11_T, R10_T, R9_T,
        R8_T, RAX_T, RCX_T, RDX_T, RSI_T, RDI_T, ORIG_RAX_T, RIP_T, CS_T,
        RFLAGS_T, RSP_T, SS_T, FS_BASE_T, GS_BASE_T, DS_T, ES_T, FS_T, GS_T
    };
    for(int i = 0 ; i < REG_SET ; i++){
        if (!strcmp(reg, register_names[i])){
            return register_numbers[i];
        }
    }
}

void writeToCache(struct user_regs_struct *retrieved_registers){
    /*
        Since user_regs_struct is homogenous in the data types it encapsulates,
        we can use pointer arithmetic to access data members.
    */
    unsigned long long int *ptr = (unsigned long long int *)retrieved_registers;
    for(int i = 0 ; i < REG_SET ; i++){
        regs[i].value = *(ptr + i);
    }
}

uint64_t readFromCache(char *reg){
    RegisterNumber register_number = getRegNumFromRegName(reg);
    for(int i = 0 ; i < REG_SET ; i++){
        if (regs[i].register_number == register_number){
            return regs[i].value;
        }
    }
}