#include "testRepository.h"
#include "repository.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

char* copyString_t1(char* string) {
	char* str = malloc(10 * sizeof(char));
	strcpy(str, string);
	return str;
}

void testRepository() {
	Repository* repo = createRepo(free, strcmp, copyString_t1);
	char* str1 = malloc(10 * sizeof(char));
	char* str2 = malloc(10 * sizeof(char));
	char* str3 = malloc(10 * sizeof(char));

	strcpy(str1, "abcdef");
	strcpy(str2, "abthfge");
	strcpy(str3, "acdghjkml");

	// tests getSizeOfRepo
	assert(getSizeOfRepo(repo) == 0);

	// tests addEntry
	addEntry(repo, str1, 0);
	assert(getSizeOfRepo(repo) == 1);

	// tests removeEntry
	removeEntry(repo, str1);
	assert(getSizeOfRepo(repo) == 0);

	addEntry(repo, str1, 0);
	addEntry(repo, str2, 0);
	addEntry(repo, str3, 0);

	// tests getItemFromRepo
	char* str4 = getItemFromRepo(repo, 1);
	assert(strcmp(str4, str2) == 0);
	free(str4);

	// tests searchRepo
	str4 = searchRepo(repo, str3);
	assert(strcmp(str4, str3) == 0);
	free(str4);

	// tests removeLastEntry
	removeLastEntry(repo);
	str4 = searchRepo(repo, str3);
	assert(str4 == NULL);

	free(str3);
	free(str2);
	free(str1);
	destroyRepo(repo);
}