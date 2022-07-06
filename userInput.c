#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "tracee.h"

#define MAX_LENGTH 128

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

void userInput(){
    char buf[MAX_LENGTH];
    while(getPrompt(buf) != NULL){
        if (checkPrefix(buf, "continue")){
            continueTracee();
        }
        else if (checkPrefix(buf, "exit") || checkPrefix(buf, "quit")){
            return;
        }
    }
}