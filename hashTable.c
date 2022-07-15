#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "hashTable.h"

extern HashTable breakpoints[HASH_TABLE_SIZE];

void initHashTable(){
    for (int i = 0 ; i < HASH_TABLE_SIZE ; i++){
        breakpoints[i].is_empty = true;
        breakpoints[i].head = NULL;
    }
}

Breakpoint *createHashTableElement(intptr_t address){
    Breakpoint *h = (Breakpoint *)malloc(sizeof(Breakpoint));
    h -> address = address;
    h -> previous = NULL;
    h -> next = NULL;
    return h;
}

void insertHashTableElement(Breakpoint *h){
    uint16_t idx = h -> address;
    if (breakpoints[idx].is_empty){
        breakpoints[idx].is_empty = false;
        breakpoints[idx].head = h;
    }
    else{
        Breakpoint *ptr = breakpoints[idx].head;
        while (ptr -> next != NULL && ptr -> address != h -> address){
            ptr = ptr -> next;
        }
        if (ptr -> address == h -> address){
            printf("Breakpoint has already been set at address %lx\n", h -> address);
            free(h);
            return;
        }
        ptr -> next = h;
    }
}

void deleteHashTableElement(intptr_t address){
    uint16_t idx = address;
    Breakpoint *ptr = breakpoints[idx].head;
    while (ptr != NULL && ptr -> address != address){
        ptr = ptr -> next;
    }
    if (ptr == NULL){
        printf("Breakpoint has not been set at addr %lx\n", address);
        return;
    }
    if (ptr -> next == NULL){
        if (ptr -> previous == NULL){
            breakpoints[idx].head = NULL;
        }
        else{
            (ptr -> previous) -> next = NULL;
        }
        free(ptr);
    }
    else{
        if (ptr -> previous == NULL){
            breakpoints[idx].head = ptr -> next;
            (ptr -> next) -> previous = NULL;
        }
        else{
            (ptr -> previous) -> next = ptr -> next;
            (ptr -> next) -> previous = ptr -> previous;
        }
        free(ptr);
    }
}