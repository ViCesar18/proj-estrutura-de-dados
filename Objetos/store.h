#ifndef STORE__H
#define STORE__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Store;
Store createStore (char cnpj[], char cpf[], char codt[], char cep[], char face[], int num, char nome[]);
Store createCodtStore (char codt[], char descricao[]);


#endif