#include"store.h"

typedef struct stStore {
    char cnpj[32], cpf [32], codt [32], cep[32], face[2], nome[32];
    int num;
} *StoreImp;

typedef struct codtStore {
    char codt[32], descricao[128];
} *CodtStoreImp;

Store createStore (char cnpj[], char cpf[], char codt[], char cep[], char face[], int num, char nome[]){
    StoreImp rStore = (StoreImp) malloc (sizeof (struct stStore));

    strcpy (rStore->cnpj, cnpj);
    strcpy (rStore->cpf, cpf);
    strcpy (rStore->codt, codt);
    strcpy (rStore->cep, cep);
    strcpy (rStore->face, face);
    rStore->num = num;
    strcpy (rStore->nome, nome);

    return rStore;
}

Store createCodtStore (char codt[], char descricao[]){
    CodtStoreImp rCodtStore = (CodtStoreImp) malloc (sizeof (struct codtStore));

    strcpy (rCodtStore->codt, codt);
    strcpy (rCodtStore->descricao, descricao);

    return rCodtStore;
}