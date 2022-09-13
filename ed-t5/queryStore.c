#include"queryStore.h"

void printStoreData (char cnpj[], HashTable stores, FILE* arq){
    Store store;
    StoreType storeType;
    Person owner;

    bool found = false;
    for(int i = 0; i < getHashTableSize(stores); i++){
        ListNode node = getHashNode(stores, i);
        while(node != NULL){
            store = getHashNodeElement(node);

            if(!strcmp(cnpj, getStoreCnpj(store))){
                found = true;
                break;
            }
            node = getHashNodeNext(node);  
        }

        if(found) break;
    }
    
    storeType = getStoreStoreType(store);
    owner = getStoreOwner(store);

    fprintf (arq, "-%s:\n\tCODT: %s\n\tDescrição: %s\n\tCNPJ: %s\n\tCEP: %s, Face: %s, Numero: %d\n\tNome do proprietário: %s %s, CPF: %s\n", getStoreName (store), getStoreTypeCodt (storeType), getStoreTypeDesc (storeType), getStoreCnpj (store), getStoreCep (store), getStoreFace (store), getStoreNum (store), getPersonName (owner), getPersonLastName (owner), getPersonCpf (owner));
}