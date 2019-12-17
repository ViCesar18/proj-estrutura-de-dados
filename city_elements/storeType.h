#ifndef STORE_TYPE_H
#define STORE_TYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *StoreType;

StoreType createStoreType (char codt[], char descricao[]);

char* getStoreTypeCodt (StoreType sType);

char* getStoreTypeDesc (StoreType sType);

#endif