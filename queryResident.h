#ifndef QUERY_RESIDENT__H
#define QUERY_RESIDENT__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "./objects/person.h"
#include "./objects/resident.h"
#include "data_structures/hash_table.h"

void treatM (FILE *arqTxt, HashTable persons, HashTable residents, char cep[]);

void printResidentData(char *cpf, HashTable residents, FILE *arqTxt);

void treatMud (FILE *arqTxt, HashTable residents, char cpf[], char cep[], char face[], int num, char compl[]);

    
#endif