#include "DynamicArray.h"
#include <stdio.h>

// creates a dynamic array object
// input: the maximum size of the array
// output: the array
DynamicArray* createDynamicArray(int cap) {
	DynamicArray* array = malloc(sizeof(DynamicArray));
	array->cap = cap;
	array->size = 0;
	array->elems = malloc(sizeof(TElem)*cap);
	return array;
}

// frees the stack from a dynamic array
// input: the dynamic array, a function for destroying the array'sitems
void destroyDynamicArray(DynamicArray* array, void(*destroy)(TElem)) {
	int i = 0;
	for (; i < array->size; i++) {
		destroy(array->elems[i]);
	}
	free(array->elems);
	free(array);
}

// adds an item to a dynamic array
// input: the array, the item, a function for copying the item
void addItem(DynamicArray* array, TElem item, TElem(*copy)(TElem)) {
	TElem cpy = copy(item);
	if (array->size == array->cap) {
		TElem* newArray = malloc(sizeof(TElem)*array->cap * 2);
		array->cap *= 2;
		int i = 0;
		for (; i < array->size; i++) {
			newArray[i] = array->elems[i];
		}
		free(array->elems);
		array->elems = newArray;
	}
	array->elems[array->size] = cpy;
	array->size++;
}

// removes an item from a dynamic array
// input: the array, the item, a function to check if 2 items are equal, a function for destroying an item
void removeItem(DynamicArray* array, TElem item, int(*equal)(TElem, TElem), void(*destroy)(TElem)) {
	int i = 0, j;
	for (; i < array->size; i++) {
		if (equal(array->elems[i], item) == 0) {
			destroy(array->elems[i]);
			for (j = i; j < array->size - 1; j++) {
				array->elems[j] = array->elems[j + 1];
			}
			array->size--;
			break;
		}
	}
}

// removes the last added item from a dynamic array
// input: the array, a function for destroying an item
void removeLastItem(DynamicArray* array, void(*destroy)(TElem)) {
	destroy(array->elems[array->size - 1]);
	array->size--;
}

// returns the size of a dynamic array
// input: the array
int getDynamicArraySize(DynamicArray* da) {
	return da->size;
}

// searches a dynamic array for a given item
// input: the array, the item, a function for comparing 2 items, a function for copying an item
// output: a copy of the item if it exists; NULL otherwise
TElem searchDynamicArray(DynamicArray* array, TElem item, int(*equal)(TElem, TElem), TElem(*copy)(TElem)) {
	int i = 0;
	for (; i < array->size; i++) {
		if (equal(item, array->elems[i]) == 0) {
			return copy(array->elems[i]);
		}
	}
	return NULL;
}

// returns a copy of the item from a dynamic array located at a given index
// input: the array, the index, a function for copying the item
TElem getItem(DynamicArray* array, int index, TElem(*copy)(TElem)) {
	return copy(array->elems[index]);
}