#ifndef STORE__H
#define STORE__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Store;
Store createStore (char cnpj[], char cpf[], char codt[], char cep[], char face[], int num, char nome[]);
Store createCodtStore (char codt[], char descricao[]);

char* getStoreCnpj (Store s);
char* getStoreCpf (Store s);
char* getStoreCep (Store s);
char* getStoreFace (Store s);
char* getStoreNome (Store s);
int getStoreNum (Store s);
char* getStoreCodt (Store s);

char* getCodt (Store sType);
char* getDescricao (Store sType);

#endif