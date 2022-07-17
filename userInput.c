#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "hashTable.h"
#include "tracee.h"

#define MAX_LENGTH 128
#define ADDRESS_LENGTH 20

static char *getPrompt(char *buf){
    printf("[dbg] ");
    char *stat = fgets(buf, MAX_LENGTH, stdin);
    size_t len = strlen(buf);
    if (buf[len - 1] == '\n'){
        buf[len - 1] = '\0';
    }
    return stat;
}

// static char *checkArgs(char *str){
//     if (
//         eol == 1 &&
//         (
//             !strcmp(str, "continue") ||
//             !strcmp(str, "exit") ||
//             !strcmp(str, "listb")
//         )
//     ){
//         printf("\033[1;31m'%s' does not take any arguments\nIgnoring arguments...\033[0m\n", str);
//         return NULL;
//     }
//     else if (eol == 0 && !strcmp(str, "read")){
//         printf("\033[1;31m'%s' missing arguments\nIgnoring command...\033[0m\n", str);
//         return NULL;
//     }
// }

static bool checkPrefix(char *inp, char *str){
    if (*inp == '\0'){
        return false;
    }
    int i = 0;
    for(i = 0 ; inp[i] != '\0' && inp[i] != ' ' ; i++){
        if (inp[i] != str[i]){
            return false;
        }
    }
    return true;
}

/*
    Currently the function assumes that input is of the form "break address"
    TODO: Enhancement: API that converts a string to a vector of strings similar to list.split in python
*/
static short parseAddress(char *buf, char **AddressStr){
    char *address = strchr(buf, ' ') + 1;
    size_t len = strlen(address);
    if (address[len - 1] == '\n'){
        address[len - 1] = '\0';
    }
    *AddressStr = address;
    if (address[1] == 'x' || address[1] == 'X'){
        return 1;
    }
    return 0;
}

/*
    Move this function later to a separate file for data type manipulation
*/
static intptr_t convertStrToAddr(char *buf){
    char *AddressStr;
    short stat = parseAddress(buf, &AddressStr);
    intptr_t address;
    if (stat){
        address = strtoul(AddressStr + 2, NULL, 16);
    }
    else{
        address = strtoul(AddressStr, NULL, 16);
    }
    return address;
}

void userInput(){
    char buf[MAX_LENGTH];
    /*
        TODO: Various argument checks
            Eg.1: Comands such as continue, exit should not have arguments
            Eg.2: Commands like break, read should have the right arguments (argc and argv)
        TODO: Add flag to TraceeInfo to check if tracee is yet to terminate
    */
    while(getPrompt(buf) != NULL){
        if (checkPrefix(buf, "continue")){
            continueTracee();
        }
        else if (checkPrefix(buf, "exit") || checkPrefix(buf, "quit")){
            killTracee();
            cleanupHashTable();
            return;
        }
        else if (checkPrefix(buf, "break")){
            intptr_t address = convertStrToAddr(buf);
            addBreakpointTracee(address);
        }
        else if (checkPrefix(buf, "delete")){
            intptr_t address = convertStrToAddr(buf);
            deleteBreakpointTracee(address);
        }
        else if (checkPrefix(buf, "list")){
            listBreakpointTracee();
        }
        else if (checkPrefix(buf, "read")){
            /* Assumption: Input is of the form read [reg|mem] [reg_name|mem_addr] */
            char *argv = strchr(buf, ' ');
            if (argv == NULL){
                printf("\033[1;31m'read' missing arguments\nIgnoring command...\033[0m\n");
                continue;
            }
            argv += 1;
            char *arg2 = strchr(argv, ' ');
            if (arg2 == NULL){
                printf("\033[1;31mMissing register/address\nIgnoring command...\033[0m\n");
                continue;
            }
            if (checkPrefix(argv, "register")){
                arg2 += 1;
                getRegValue(arg2);
            }
            else if (checkPrefix(argv, "memory")){
                arg2 += 1;
                intptr_t address;
                if (arg2[1] == 'X' || arg2[1] == 'x'){
                    address = strtoull(arg2 + 2, NULL, 16);
                }
                else{
                    address = strtoull(arg2, NULL, 16);
                }
                getMemValue(address);
            }
        }
    }
}