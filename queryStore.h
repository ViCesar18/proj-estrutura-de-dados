#ifndef QUERY_STORE__H
#define QUERY_STORE__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "./objects/store.h"
#include "./objects/person.h"
#include "./objects/storeType.h"
#include "data_structures/hash_table.h"

void printStoreData (char cnpj[], HashTable stores, FILE* arq);

#endif