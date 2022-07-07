#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
    size_t InpLen = strlen(inp), StrLen = strlen(str);
    if (InpLen == 0 || InpLen > StrLen){
        return false;
    }
    for(int i = 0 ; i < InpLen && inp[i] != '\0' ; i++){
        if (inp[i] != str[i]){
            return false;
        }
    }
    return true;
}

static short parseAddress(char *address){
    fgets(address, ADDRESS_LENGTH, stdin);
    size_t len = strlen(address);
    if (address[len - 1] == '\n'){
        address[len - 1] = '\0';
    }
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
            return;
        }
        else if (checkPrefix(buf, "break")){
            printf("Address to break at: ");
            char AddressStr[ADDRESS_LENGTH];
            short stat = parseAddress(AddressStr);
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