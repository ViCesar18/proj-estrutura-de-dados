#include"store.h"

typedef struct stStore {
    char cnpj[32], cpf [32],  cep[32], face[2], nome[32];
    char codt[32];
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

char* getStoreCnpj (Store s){
    StoreImp store = (StoreImp) s;

    return store->cnpj;
} 

char* getStoreCpf (Store s){
    StoreImp store = (StoreImp) s;

    return store->cpf;
}   

char* getStoreCep (Store s){
    StoreImp store = (StoreImp) s;

    return store->cep;
}  
 
char* getStoreFace (Store s){
    StoreImp store = (StoreImp) s;

    return store->face;
} 

char* getStoreNome (Store s){
    StoreImp store = (StoreImp) s;

    return store->nome;
} 

int getStoreNum (Store s){
    StoreImp store = (StoreImp) s;

    return store->num;
}

char* getStoreCodt (Store s){
    StoreImp store = (StoreImp) s;

    return store->codt;
}

char* getCodt (Store sType){
    CodtStoreImp storeType = (CodtStoreImp) sType;

    return storeType->codt;
}

char* getDescricao (Store sType){
    CodtStoreImp storeType = (CodtStoreImp) sType;

    return storeType->descricao;
}
