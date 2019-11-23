#include "hash_table.h"

typedef struct ListNodeSt{
	Element element;
	char *key;
	struct ListNodeSt *next;
} *ListNodeImp;

typedef struct HashTableSt{
	int size;
	ListNodeImp *list;
	void (*destroy)(Element);
} *HashTableImp;

int getHashTableSize(HashTable h){
	HashTableImp hash = (HashTableImp) h;

	return hash->size;
}

ListNode getHashNode(HashTable h, int i){
	HashTableImp hash = (HashTableImp) h;

	return hash->list[i];
}

ListNode getHashNodeNext(ListNode n){
	ListNodeImp node = (ListNodeImp) n;

	return node->next;
}

Element getHashNodeElement(ListNode n){
	ListNodeImp node = (ListNodeImp) n;

	return node->element;
}

HashTable createHashTable(int size, void (*destroy)(Element)){
	HashTableImp hash = (HashTableImp) malloc(sizeof(struct HashTableSt));
	hash->size = size;
	hash->list = (ListNodeImp *) malloc(size * sizeof(ListNodeImp));
	memset(hash->list, 0, size * sizeof(ListNodeImp));
	hash->destroy = destroy;

	return hash;
}

unsigned long long hashFunction(char *key){
	unsigned long long position = 197;
	int len = strlen(key);

	for(int i = 0; i < len; i++){
		position = position * 31 + key[i];
	}

	return position;
}

bool insertHashTable(HashTable h, char *key, Element element){
	HashTableImp hash = (HashTableImp) h;

	unsigned long long position = hashFunction(key) % hash->size;

	ListNodeImp node = (ListNodeImp) malloc(sizeof(struct ListNodeSt));
	node->element = element;
	node->key = key;
	node->next = NULL;

	if(hash->list[position] == NULL){
		hash->list[position] = node;
		return true;
	}
	else{
		ListNodeImp currentNode = hash->list[position];

		while(currentNode->next != NULL)
			currentNode = currentNode->next;

		currentNode->next = node;
		return true;
	}

	free(node);
	return false;
}

bool removeHashTable(HashTable h, char *key){
	HashTableImp hash = (HashTableImp) h;

	unsigned long long position = hashFunction(key) % hash->size;
	ListNodeImp previousNode = NULL;
	ListNodeImp currentNode = hash->list[position];
	while(currentNode->next != NULL && strcmp(currentNode->key, key) != 0){
		previousNode = currentNode;
		currentNode = currentNode->next;
	}

	if(hash->list[position] == NULL)
		return false;

	if(previousNode == NULL){
		hash->list[position] = currentNode->next;
	}
	else{
		previousNode->next = currentNode->next;
	}
	
	free(currentNode);
	return true;
}

Element searchHashTable(HashTable h, char *key){
	HashTableImp hash = (HashTableImp) h;
	int position = hashFunction(key) % hash->size;
	ListNodeImp currentNode = hash->list[position];

	while(currentNode != NULL && strcmp(key, currentNode->key) != 0){
		currentNode = currentNode->next;
	}
	
	if(currentNode == NULL)
		return NULL;

	return currentNode->element;
}

void destroyHashTable(HashTable h){
	HashTableImp hash = (HashTableImp) h;

	for(int i = 0; i < hash->size; i++){
		ListNodeImp node = hash->list[i];

		while(node != NULL){
			if(hash->destroy != NULL){
				hash->destroy(node->element);
			}
			ListNodeImp nextNode = node->next;
			free(node);
			node = nextNode;
		}
	}

	free(hash->list);
	free(hash);
}