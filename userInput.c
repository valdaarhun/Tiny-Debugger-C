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

static bool checkPrefix(char *inp, char *str){
    if (*inp == '\0'){
        return false;
    }
    for(int i = 0 ; inp[i] != '\0' && inp[i] != ' ' ; i++){
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
static short parseAddress(char * buf, char **AddressStr){
    char *address = strstr(buf, " ") + 1;
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

void userInput(){
    char buf[MAX_LENGTH];
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
            char *AddressStr;
            short stat = parseAddress(buf, &AddressStr);
            intptr_t address;
            if (stat){
                address = strtoul(AddressStr + 2, NULL, 16);
            }
            else{
                address = strtoul(AddressStr, NULL, 16);
            }
            breakpointTracee(address);
        }
    }
}