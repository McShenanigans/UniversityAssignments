#include "DynamicArray.h"
#include "testDynArray.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

// function for creating a copy of a string
// input: the string
// output: a copy of the string
char* copyString_t2(char* string) {
	char* str = malloc(10 * sizeof(char));
	strcpy(str, string);
	return str;
}

void testDynArray() {
	DynamicArray* da = createDynamicArray(2);
	char* str1 = malloc(10 * sizeof(char));
	char* str2 = malloc(10 * sizeof(char));
	char* str3 = malloc(10 * sizeof(char));

	strcpy(str1, "abcdef");
	strcpy(str2, "abthfge");
	strcpy(str3, "acdghjkml");
	
	// tests addItem
	assert(da->size == 0);
	addItem(da, str1, copyString_t2);
	assert(da->size == 1);

	//tests removeItem
	removeItem(da, str1, strcmp, free);
	assert(da->size == 0);

	addItem(da, str1, copyString_t2);
	addItem(da, str2, copyString_t2);
	addItem(da, str3, copyString_t2);

	// tests getItem
	char* str4 = getItem(da, 1, copyString_t2);
	assert(strcmp(str4, str2) == 0);
	free(str4);

	// tests searchDynamicArray
	str4 = searchDynamicArray(da, str1, strcmp, copyString_t2);
	assert(strcmp(str4, str1) == 0);
	free(str4);

	// tests removeLastItem
	removeLastItem(da, free);
	assert(da->size == 2);
	str4 = searchDynamicArray(da, str3, strcmp, copyString_t2);
	assert(str4 == NULL);

	free(str3);
	free(str2);
	free(str1);
	destroyDynamicArray(da, free);
}