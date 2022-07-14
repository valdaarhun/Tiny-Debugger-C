#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>

#define HASH_TABLE_SIZE 0x10000

struct HashTableElement{
    intptr_t address;
    struct HashTableElement *next;
    struct HashTableElement *previous;
};

typedef struct HashTableElement HashTableElement;

typedef struct{
    bool is_empty;
    HashTableElement *head;
}HashTable;

void initHashTable();

#endif