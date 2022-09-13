#include "storeType.h"

typedef struct codtStore {
    char codt[32], descricao[128];
} *CodtStoreImp;

StoreType createStoreType (char codt[], char descricao[]){
    CodtStoreImp rCodtStore = (CodtStoreImp) malloc (sizeof (struct codtStore));

    strcpy (rCodtStore->codt, codt);
    strcpy (rCodtStore->descricao, descricao);

    return rCodtStore;
}

char* getStoreTypeCodt (StoreType sType){
    CodtStoreImp storeType = (CodtStoreImp) sType;

    return storeType->codt;
}

char* getStoreTypeDesc (StoreType sType){
    CodtStoreImp storeType = (CodtStoreImp) sType;

    return storeType->descricao;
}