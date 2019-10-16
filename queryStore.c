#include"queryStore.h"

void printStoreData (char cnpj[], List stores, List persons, List storeTypes, FILE* arq){
    Store store;
    Store storeType;
    Person person;

    for (int i = getFirst (stores); i != getNulo (); i = getNext (stores, i)){
        store = getElementByIndex (stores, i);
        char* cnpjStore = getStoreCnpj (store);
        char* cpfStore = getStoreCpf (store);

        for (int i = getFirst (persons); i != getNulo(); i = getNext (persons, i)){
            person = getElementByIndex (persons, i);
            char* cpfPerson = getPersonCpf (person);

            if (strcmp (cpfPerson, cpfStore) == 0) break;
        }
        for (int i = getFirst (storeTypes); i != getNulo (); i = getNext (storeTypes, i)){
            storeType = getElementByIndex (storeTypes, i);
            char* codt = getCodt (storeType);

            if (strcmp (codt, getStoreCodt (store)) == 0) break;
        }

        if (strcmp(cnpjStore, cnpj) == 0){
            fprintf (arq, "-%s:\n\tCodt: %s\n\tDescricao: %s\n\tCNPJ: %s\n\tCEP: %s, Face: %s ,Numero: %d\n\tNome do proprietario: %s %s, CPF: %s\n", getStoreNome (store), getCodt (storeType), getDescricao (storeType), getStoreCnpj (store), getStoreCep (store), getStoreFace (store), getStoreNum (store), getPersonNome (person), getPersonSobrenome (person), getPersonCpf (person));
        }
    }
}