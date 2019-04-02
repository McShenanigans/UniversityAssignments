#pragma once
#include "DynamicArray.h"

typedef struct{
	DynamicArray* list;
	int(*equal)(TElem, TElem);
	void(*destroy)(TElem);
	TElem(*copy)(TElem);
}Repository;

Repository* createRepo(void(*destroy)(TElem), int(*equal)(TElem, TElem), TElem(*copy)(TElem));

void destroyRepo(Repository*);
void removeLastEntry(Repository*);

int addEntry(Repository*, TElem, int);
int removeEntry(Repository*, TElem);
int getSizeOfRepo(Repository*);

TElem searchRepo(Repository*, TElem);
TElem getItemFromRepo(Repository*, int);