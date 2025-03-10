#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 100

typedef enum { INT_TYPE, FLOAT_TYPE } DataType;

typedef struct {
    char *name;
    DataType type;
    int stackOffset;
} SymbolEntry;

typedef struct {
    SymbolEntry entries[MAX_SYMBOLS];
    int count;
    int stackPointer;
} SymbolTable;

void initSymbolTable(SymbolTable *table);
void addSymbol(SymbolTable *table, const char *name, DataType type);
SymbolEntry* findSymbol(SymbolTable *table, const char *name);

#endif
