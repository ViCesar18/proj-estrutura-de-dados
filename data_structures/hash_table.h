#ifndef HASH__TABLE
#define HASH__TABLE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef void *HashTable;
typedef void *Element;

/*Cria e retorna uma tabela de espalhamento*/
HashTable createHashTable(int size, void (*destroy)(Element));

/*Insere element na tabela h com a chave key. Retorna true caso insira, false caso contrario*/
bool insertHashTable(HashTable h, char *key, Element element);

/*Remove o no que tenha a chave key da tabela h. Retorna 1 caso remova, false caso contrario*/
bool removeHashTable(HashTable h, char *key);

/*Busca e retorna o elemento armazenado na tabela h cuja chave seja key*/
Element searchHashTable(HashTable h, char *key);

/*Libera a memoria usada pela tabela de espalhamento*/
void destroyHashTable(HashTable h);

#endif