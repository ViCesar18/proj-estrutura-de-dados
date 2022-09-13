#include"store.h"

typedef struct stStore {
    char cnpj[32], cep[32], face[2], nome[32];
    int num;
    double x, y;
    StoreType storeType;
    Person owner;
    Block block;
} *StoreImp;

Store createStore (char cnpj[], char cpf[], char codt[], char cep[], char face[], int num, char nome[], HashTable storeTypes, HashTable persons, Block block){
    StoreImp store = (StoreImp) malloc (sizeof (struct stStore));

    double xB = getBlockX(block), yB = getBlockY(block), wB = getBlockW(block), hB = getBlockH(block);

    if(!strcmp(face, "N")){
        store->x = xB + num;
        store->y = yB + hB;
    }
    else if(!strcmp(face, "S")){
        store->x = xB + num;
        store->y = yB;
    }
    else if(!strcmp(face, "O")){
        store->x = xB + wB;
        store->y = yB + num;
    }
    else if(!strcmp(face, "L")){
        store->x = xB;
        store->y = yB + num;
    }

    strcpy (store->cnpj, cnpj);
    strcpy (store->cep, cep);
    strcpy (store->face, face);
    store->num = num;
    strcpy (store->nome, nome);

    bool found = false;
    for(int i = 0; i < getHashTableSize(storeTypes); i++){
        ListNode node = getHashNode(storeTypes, i);
        while(node != NULL){
            StoreType storeType = getHashNodeElement(node);

            if(!strcmp(codt, getStoreTypeCodt(storeType))){
                found = true;
                store->storeType = storeType;
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
                store->owner = person;
                break;
            }
            node = getHashNodeNext(node);
        }

        if(found) break;
    }

    store->block = block;

    return store;
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

double getStoreX(Store s){
    StoreImp store = (StoreImp) s;

    return store->x;
}

double getStoreY(Store s){
    StoreImp store = (StoreImp) s;

    return store->y;
}

StoreType getStoreStoreType(Store s){
    StoreImp store = (StoreImp) s;

    return store->storeType;
}

Block getStoreBlock(Store s){
    StoreImp store = (StoreImp) s;

    return store->block;
}

void destroyStore(Store s){
    
    free(s);
}