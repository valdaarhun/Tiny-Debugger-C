#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>

#define HASH_TABLE_SIZE 0x10000

struct Breakpoint{
    intptr_t address;
    int8_t byte;
    struct Breakpoint *next;
    struct Breakpoint *previous;
};

typedef struct Breakpoint Breakpoint;

typedef struct{
    bool is_empty;
    Breakpoint *head;
}HashTable;

void initHashTable();
void insertBreakpoint(intptr_t, int8_t);
void cleanupHashTable();

#endif