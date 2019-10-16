#ifndef QUERY_STORE__H
#define QUERY_STORE__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "./Objetos/store.h"
#include "./Objetos/person.h"

void printStoreData (char cnpj[], List stores, List persons, List storeTypes, FILE* arq);


#endif