#include"store.h"

typedef struct stStore {
    char cnpj[32],  cep[32], face[2], nome[32];
    int num;
    StoreType storeType;
    Person owner;
} *StoreImp;

Store createStore (char cnpj[], char cpf[], char codt[], char cep[], char face[], int num, char nome[], HashTable storeTypes, HashTable persons){
    StoreImp rStore = (StoreImp) malloc (sizeof (struct stStore));

    strcpy (rStore->cnpj, cnpj);
    strcpy (rStore->cep, cep);
    strcpy (rStore->face, face);
    rStore->num = num;
    strcpy (rStore->nome, nome);

    bool found = false;
    for(int i = 0; i < getHashTableSize(storeTypes); i++){
        ListNode node = getHashNode(storeTypes, i);
        while(node != NULL){
            StoreType storeType = getHashNodeElement(node);

            if(!strcmp(codt, getStoreTypeCodt(storeType))){
                found = true;
                rStore->storeType = storeType;
                break;
            }
            node = getHashNodeNext(node);
        }

        if(found) break;
    }

    found = false;
    for(int i = 0; i < getHashTableSize(persons); i++){
        ListNode node = getHashNode(persons, i);
        while(node != NULL){
            Person person = getHashNodeElement(node);
            if(!strcmp(cpf, getPersonCpf(person))){
                found = true;
                rStore->owner = person;
                break;
            }
            node = getHashNodeNext(node);
        }

        if(found) break;
    }

    return rStore;
}

char* getStoreCnpj (Store s){
    StoreImp store = (StoreImp) s;

    return store->cnpj;
} 

char* getStoreOwner (Store s){
    StoreImp store = (StoreImp) s;

    return store->owner;
}   

char* getStoreCep (Store s){
    StoreImp store = (StoreImp) s;

    return store->cep;
}  
 
char* getStoreFace (Store s){
    StoreImp store = (StoreImp) s;

    return store->face;
} 

char* getStoreName (Store s){
    StoreImp store = (StoreImp) s;

    return store->nome;
} 

int getStoreNum (Store s){
    StoreImp store = (StoreImp) s;

    return store->num;
}

StoreType getStoreStoreType(Store s){
    StoreImp store = (StoreImp) s;

    return store->storeType;
}

void destroyStore(Store s){
    
    free(s);
}