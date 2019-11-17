#ifndef QUERY_STORE__H
#define QUERY_STORE__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "./city_elements/store.h"
#include "./city_elements/person.h"
#include "./city_elements/storeType.h"
#include "data_structures/hash_table.h"

void printStoreData (char cnpj[], HashTable stores, FILE* arq);

#endif