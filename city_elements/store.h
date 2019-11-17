#ifndef STORE__H
#define STORE__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "storeType.h"
#include "person.h"
#include "../data_structures/hash_table.h"

typedef void *Store;
Store createStore (char cnpj[], char cpf[], char codt[], char cep[], char face[], int num, char nome[], HashTable storeTypes, HashTable persons);
Store createCodtStore (char codt[], char descricao[]);

char* getStoreCnpj (Store s);
char* getStoreOwner (Store s);
char* getStoreCep (Store s);
char* getStoreFace (Store s);
char* getStoreName (Store s);
int getStoreNum (Store s);
char* getStoreCodt (Store s);
StoreType getStoreStoreType(Store s);

void destroyStore(Store s);

#endif