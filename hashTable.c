#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "hashTable.h"

extern HashTable hash_table[HASH_TABLE_SIZE];

void initHashTable(){
    for (int i = 0 ; i < HASH_TABLE_SIZE ; i++){
        hash_table[i].is_empty = true;
        hash_table[i].head = NULL;
    }
}

HashTableElement *createHashTableElement(intptr_t address){
    HashTableElement *h = (HashTableElement *)malloc(sizeof(HashTableElement));
    h -> address = address;
    h -> previous = NULL;
    h -> next = NULL;
    return h;
}

void insertHashTableElement(HashTableElement *h){
    uint16_t idx = h -> address;
    if (hash_table[idx].is_empty){
        hash_table[idx].is_empty = false;
        hash_table[idx].head = h;
    }
    else{
        HashTableElement *ptr = hash_table[idx].head;
        while (ptr -> next != NULL && ptr -> address != h -> address){
            ptr = ptr -> next;
        }
        if (ptr -> address == h -> address){
            printf("Breakpoint has already been set at address %lx", h -> address);
            free(h);
            return;
        }
        ptr -> next = h;
    }
}

void deleteHashTableElement(intptr_t address){
    uint16_t idx = address;
    HashTableElement *ptr = hash_table[idx].head;
    while (ptr != NULL && ptr -> address != address){
        ptr = ptr -> next;
    }
    if (ptr == NULL){
        printf("Breakpoint has not been set at addr %lx", address);
        return;
    }
    if (ptr -> next == NULL){
        if (ptr -> previous == NULL){
            hash_table[idx].head = NULL;
        }
        else{
            (ptr -> previous) -> next = NULL;
        }
        free(ptr);
    }
    else{
        if (ptr -> previous == NULL){
            hash_table[idx].head = ptr -> next;
            (ptr -> next) -> previous = NULL;
        }
        else{
            (ptr -> previous) -> next = ptr -> next;
            (ptr -> next) -> previous = ptr -> previous;
        }
        free(ptr);
    }
}