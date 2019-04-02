#pragma once
#include "Windows.h"
typedef void* TElem;

typedef struct {
	TElem* elems;
	int size;
	int cap;
}DynamicArray;

DynamicArray* createDynamicArray(int);

void destroyDynamicArray(DynamicArray*, void(*destroy)(TElem));
void addItem(DynamicArray*, TElem, TElem(*copy)(TElem));
void removeItem(DynamicArray*, TElem, int(*equal)(TElem, TElem), void(*destroy)(TElem));
void removeLastItem(DynamicArray*, void(*destroy)(TElem));

int getDynamicArraySize(DynamicArray*);

TElem searchDynamicArray(DynamicArray*, TElem, int(*equal)(TElem, TElem), TElem(*copy)(TElem));
TElem getItem(DynamicArray*, int, TElem(*copy)(TElem));
