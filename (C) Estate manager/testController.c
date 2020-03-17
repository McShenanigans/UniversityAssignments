#include "controller.h"
#include "testController.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void testController() {
	Controller* c = createController();
	char* str1 = malloc(10 * sizeof(char));
	char* str2 = malloc(10 * sizeof(char));
	char* str3 = malloc(10 * sizeof(char));

	strcpy(str1, "abcdef");
	strcpy(str2, "abthfge");
	strcpy(str3, "acdghjkml");

	// tests getSize
	assert(getSize(c) == 0);

	// tests newEntry
	newEntry(c, "a", str1, 0, 0, 1);
	assert(getSize(c) == 1);

	// tests dropEntry
	dropEntry(c, str1);
	assert(getSize(c) == 0);

	// tests undo
	undo(c);
	assert(getSize(c) == 1);

	// tests redo
	redo(c);
	assert(getSize(c) == 0);

	newEntry(c, "a", str1, 30, 20, 0);
	newEntry(c, "a", str2, 20, 50, 0);
	newEntry(c, "a", str3, 10, 29, 0);
	
	// tests updateEntry & getEstateString
	updateEntry(c, str1, 1, "b", 0);
	char* str = getEstateString(c, 0);
	char* str5 = "type: b; address: abcdef; price: 30; surface: 0\n";
	assert(strcmp(str, str5) == 0);
	free(str);

	int* found = malloc(4*sizeof(int));
	
	//tests searchForMatches
	int len = searchForMatches(c, found, "ab");
	assert(len == 2);
	free(found);

	// tests searchBySurface
	found = malloc(4 * sizeof(int));
	len = searchBySurface(c, found, 30);
	assert(len == 1);
	free(found);

	// tests searchByTypeSurface
	found = malloc(4 * sizeof(int));
	len = searchByTypeSurface(c, found, "b", 15);
	assert(len == 1);
	free(found);

	free(str3);
	free(str2);
	free(str1);
	destroyController(c);
}