#include "controller.h"

// checks if a string is present in another string
// input: the string to search for; the string to search in
// output: 1 if the string is found; 0 otherwise
int isThere(char* s1, char* s2) {
	if (strcmp(s1, "") == 0 || strcmp(s1, " ") == 0 || strcmp(s1, "\t") == 0) return 1;
	if (strlen(s1) > strlen(s2)) return 0;
	int i = 0, j, count = 0;
	for (; i <= strlen(s2) - strlen(s1); i++) {
		if (s1[0] == s2[i]) {
			count = 1;
			for (j = 1; j < strlen(s1); j++) {
				if (s1[j] == s2[i + j]) {
					count++;
				}
			}
			if (count == strlen(s1))return 1;
		}
	}
	return 0;
}

// converts an int into a string
// input: the int
// output: a string containing the int
char* intToString(int a) {
	int p = a, l = 0;
	do {
		a /= 10;
		l++;
	} while (a);
	char* string = malloc((l+1) * sizeof(char));
	string[l] = 0;
	while (l) {
		string[--l] = p % 10 + 48;
		p /= 10;
	}
	return string;
}

// sorts DynamicIntArray by the prices of the estaes its elements point to
// input: the controller with the repo containing the estats we want ot sort, the array
void sortByPrice(Controller* c, int* array, int len) {
	int i = 0, j, a;
	Estate* estate = NULL, *estate2 = NULL, *swapEstate = NULL;
	for (i = 0; i < len - 1; i++) {
		estate = getItemFromRepo(c->repo, array[i]);
		for (j = i + 1; j < len; j++) {
			estate2 = getItemFromRepo(c->repo, array[j]);
			if (estate->price > estate2->price) {
				a = array[j];
				array[j] = array[i];
				array[i] = a;
				swapEstate = estate2;
				estate2 = estate;
				estate = swapEstate;
			}
			destroyEstate(estate2);
		}
		destroyEstate(estate);
	}
}

// returns a copy of a string
// input: the string
char* copyString(char* string) {
	char* str = malloc(strlen(string) + 1);
	strcpy(str, string);
	return str;
}

// empties a controller's redo stack
// input: the controller
void emptyRedo(Controller* c) {
	destroyRepo(c->redoAddress);
	destroyRepo(c->redoOps);
	destroyRepo(c->redoObj);
	c->redoObj = createRepo(destroyEstate, equalEstates, copyEstate);
	c->redoOps = createRepo(free, strcmp, copyString);
	c->redoAddress = createRepo(free, strcmp, copyString);
}

// creates a controller object
// output: a controller object
Controller* createController() {
	Controller* c = malloc(sizeof(Controller));
	c->redoAddress = createRepo(free, strcmp, copyString);
	c->undoAddress = createRepo(free, strcmp, copyString);
	c->redoObj = createRepo(destroyEstate, equalEstates, copyEstate);
	c->redoOps = createRepo(free, strcmp, copyString);
	c->undoObj = createRepo(destroyEstate, equalEstates, copyEstate);
	c->undoOps = createRepo(free, strcmp, copyString);
	c->repo = createRepo(destroyEstate, equalEstates, copyEstate);
	return c;
}

// frees the heap from a controller
// input: the controller
void destroyController(Controller* c) {
	destroyRepo(c->repo);
	destroyRepo(c->undoOps);
	destroyRepo(c->undoObj);
	destroyRepo(c->redoOps);
	destroyRepo(c->redoObj);
	destroyRepo(c->undoAddress);
	destroyRepo(c->redoAddress);
	free(c);
}

// adds an estate to a controller's repository
// input: the controller, the estate's type, address, price, surface and a flag for undo/redo
// output: 1 if the operation was succesful; 0 otherwise
int newEntry(Controller* c, char* type, char* address, int price, int surface, int addUndo) {
	int result = 0;
	Estate* estate = createEstate(type, address, price, surface);
	result = addEntry(c->repo, estate, 0);
	if (result == 1 && addUndo == 1) {
		emptyRedo(c);
		addEntry(c->undoObj, estate, 1);
		addEntry(c->undoOps, "add", 1);
	}
	destroyEstate(estate);
	return result;
}

// removes an estate from a controller's repository
// input: the controller, the address of the estate
// output: 1 if the operation was succesful; 0 otherwise
int dropEntry(Controller* c, char* address) {
	int result = 0;
	Estate* estate = createEstate("a", address, 0, 0);
	Estate* estatecopy = searchRepo(c->repo, estate);
	result = removeEntry(c->repo, estate);
	if (result == 1) {
		emptyRedo(c);
		addEntry(c->undoObj, estatecopy, 1);
		addEntry(c->undoOps, "remove", 1);
	}
	if (estatecopy != NULL) {
		destroyEstate(estatecopy);
	}
	destroyEstate(estate);
	return result;
}

// updates an estate from a controller's repository
// input: the controller, the address of the estate, the field to update, the new value of the field, flag for undo/redo
void updateEntry(Controller* c, char* address, int objToUpdate, char* newValue, int fromUR) {
	Estate* estateToSearch = createEstate("a", address, 0, 0);
	Estate* estate = searchRepo(c->repo, estateToSearch);
	if (estate != NULL) {
		if (fromUR == 0) {
			emptyRedo(c);
			addEntry(c->undoObj, estate, 1);
			addEntry(c->undoOps, "update", 1);
		}
		removeEntry(c->repo, estate);
		if (objToUpdate == 1) {
			setType(estate, newValue);
		}
		else if (objToUpdate == 2) {
			setAddress(estateToSearch, newValue);
			Estate* estate1 = searchRepo(c->repo, estateToSearch);
			if (estate1 == NULL) {
				if (fromUR == 0) {
					addEntry(c->undoAddress, estate->address, 1);
					addEntry(c->undoAddress, newValue, 1);
				}
				setAddress(estate, newValue);
			}
			else {
				destroyEstate(estate1);
			}
		}
		else if (objToUpdate == 3) {
			setPrice(estate, atoi(newValue));
		}
		else if (objToUpdate == 4) {
			setSurface(estate, atoi(newValue));
		}
		addEntry(c->repo, estate, 0);
		destroyEstate(estate);
	}
	destroyEstate(estateToSearch);
}

// searches for estates which's address partially match a given string
// input: the controller, a list of ints for remembering the matching estate's indexes in the repository, the string to match
// output: the number of results
int searchForMatches(Controller* c, int* found, char* searchString) {
	int len = 0, i = 0;
	Estate* estate = NULL;
	for (; i < getSizeOfRepo(c->repo); i++) {
		estate = getItemFromRepo(c->repo, i);
		if (isThere(searchString, estate->address)) found[len++] = i;
		destroyEstate(estate);
	}
	sortByPrice(c, found, len);
	return len;
}

// searches for estates the have the surface equal to a given value
// input: the controller, a int list for remembering the matching estate's indexes in the repo, the value of the surface
// output: the number of results
int searchBySurface(Controller* c, int* found, int surface) {
	Estate* estate = NULL;
	int i = 0, len = 0;
	for (; i < getSizeOfRepo(c->repo); i++) {
		estate = getItemFromRepo(c->repo, i);
		if (estate->surface == surface) { 
			found[len++] = i; 
		}
		destroyEstate(estate);
	}
	sortByPrice(c, found, len);
	return len;
}

// searches for estates of a given type with surface greater than a given value
// input: the controller, a int list for remembering the matching estate's indexes in the repo, the estatevtype, the value of the surface
// output: the number of results
int searchByTypeSurface(Controller *c, int *found, char *type, int surface){
	Estate* estate = NULL;
	int len = 0, i = 0;
	for (; i < getSizeOfRepo(c->repo); i++) {
		estate = getItemFromRepo(c->repo, i);
		if (strcmp(estate->type, type) == 0 && estate->surface > surface) found[len++] = i;
		destroyEstate(estate);
	}
	sortByPrice(c, found, len);
	return len;
}

// returns the number of entries in a controller's repo
// input: the controller
int getSize(Controller* c) {
	return getSizeOfRepo(c->repo);
}

// returns a string containing an estate's data
// input: the controller, the index of the estate in the controller's repo
char* getEstateString(Controller* c, int index) {
	Estate* estate = getItemFromRepo(c->repo, index);
	char* str = estateToString(estate);
	destroyEstate(estate);
	return str;
}

// undoes the last performed operation
// input: the controller
void undo(Controller* c) {
	int len = getSizeOfRepo(c->undoObj);
	if (len > 0) {
		char* op = getItemFromRepo(c->undoOps, len - 1);
		Estate* estate = getItemFromRepo(c->undoObj, len - 1);
		if (strcmp(op, "add") == 0) {
			removeEntry(c->repo, estate);
			addEntry(c->redoObj, estate, 1);
		}
		else if (strcmp(op, "remove") == 0) {
			addEntry(c->repo, estate, 0);
			addEntry(c->redoObj, estate, 1);
		}
		else if (strcmp(op, "update") == 0) {
			Estate* estateMod = searchRepo(c->repo, estate);
			if (estateMod != NULL) {
				if (strcmp(estateMod->type, estate->type) != 0) {
					updateEntry(c, estateMod->address, 1, estate->type, 1);
				}
				else if (estateMod->price != estate->price) {
					char* string = intToString(estate->price);
					updateEntry(c, estateMod->address, 3, string, 1);
					free(string);
				}
				else if (estateMod->surface != estate->surface) {
					char* string = intToString(estate->surface);
					updateEntry(c, estateMod->address, 4, string, 1);
					free(string);
				}
				addEntry(c->redoObj, estateMod, 1);
				destroyEstate(estateMod);
			}
			else {
				int len1 = getSizeOfRepo(c->undoAddress);
				char* address1 = getItemFromRepo(c->undoAddress, len1 - 1);
				char* address2 = getItemFromRepo(c->undoAddress, len1 - 2);
				
				Estate* newEstate = createEstate("a", address1, 0, 0);
				estateMod = searchRepo(c->repo, newEstate);
				
				addEntry(c->redoObj, estateMod, 1);
				destroyEstate(estateMod);
				destroyEstate(newEstate);

				updateEntry(c, address1, 2, address2, 1);

				addEntry(c->redoAddress, address2, 1);
				addEntry(c->redoAddress, address1, 1);
				
				free(address2);
				free(address1);

				removeLastEntry(c->undoAddress);
				removeLastEntry(c->undoAddress);
			}
		}
		addEntry(c->redoOps, op, 1);
		removeLastEntry(c->undoObj);
		removeLastEntry(c->undoOps);
		destroyEstate(estate);
		free(op);
	}
 }

// redoes the last undone operation
// input: the controller
void redo(Controller* c) {
	int len = getSizeOfRepo(c->redoObj);
	if (len > 0) {
		char* op = getItemFromRepo(c->redoOps, len - 1);
		Estate* estate = getItemFromRepo(c->redoObj, len - 1);
		if (strcmp(op, "add") == 0) {
			addEntry(c->repo, estate, 0);
			addEntry(c->undoObj, estate, 1);
		}
		else if (strcmp(op, "remove") == 0) {
			removeEntry(c->repo, estate);
			addEntry(c->undoObj, estate, 1);
		}
		else if (strcmp(op, "update") == 0) {
			Estate* estateMod = searchRepo(c->repo, estate);
			if (estateMod != NULL) {
				if (strcmp(estateMod->type, estate->type) != 0) {
					updateEntry(c, estateMod->address, 1, estate->type, 1);
				}
				else if (estateMod->price != estate->price) {
					char* string = intToString(estate->price);
					updateEntry(c, estateMod->address, 3, string, 1);
					free(string);
				}
				else if (estateMod->surface != estate->surface) {
					char* string = intToString(estate->surface);
					updateEntry(c, estateMod->address, 4, string, 1);
					free(string);
				}
				addEntry(c->undoObj, estateMod, 1);
				destroyEstate(estateMod);
			}
			else {
				int len1 = getSizeOfRepo(c->redoAddress);
				char* address1 = getItemFromRepo(c->redoAddress, len1 - 1);
				char* address2 = getItemFromRepo(c->redoAddress, len1 - 2);

				Estate* newEstate = createEstate("a", address2, 0, 0);
				estateMod = searchRepo(c->repo, newEstate);

				updateEntry(c, address2, 2, address1, 1);

				addEntry(c->undoObj, estateMod, 1);
				addEntry(c->undoAddress, address2, 1);
				addEntry(c->undoAddress, address1, 1);

				destroyEstate(estateMod);
				destroyEstate(newEstate);
				free(address2);
				free(address1);

				removeLastEntry(c->redoAddress);
				removeLastEntry(c->redoAddress);
			}
		}
		addEntry(c->undoOps, op, 1);
		removeLastEntry(c->redoObj);
		removeLastEntry(c->redoOps);
		destroyEstate(estate);
		free(op);
	}
}

/*void printUR(Controller* c) {
	Estate* estate = NULL;
	char *op = NULL, *estateString = NULL;
	int i = 0;
	printf("\nundos:");
	for (; i < getSizeOfRepo(c->undoObj); i++) {
		estate = getItemFromRepo(c->undoObj, i);
		op = getItemFromRepo(c->undoOps, i);
		estateString = estateToString(estate);

		printf("\n%s %s", op, estateString);
		
		free(estateString);
		free(op); 
		destroyEstate(estate);
	}
	printf("\nredos:");
	for (i = 0; i < getSizeOfRepo(c->redoObj); i++) {
		estate = getItemFromRepo(c->redoObj, i);
		op = getItemFromRepo(c->redoOps, i);
		estateString = estateToString(estate);

		printf("\n%s %s", op, estateString);

		free(estateString);
		free(op);
		destroyEstate(estate);
	}
	printf("\nundo address stack:");
	for (i = 0; i < getSizeOfRepo(c->undoAddress); i+=2) {
		char* address1 = getItemFromRepo(c->undoAddress, i);
		char* address2 = getItemFromRepo(c->undoAddress, i + 1);
		printf("\n%s %s", address1, address2);
		free(address2);
		free(address1);
	}
	printf("\nredo address stack:");
	for (i = 0; i < getSizeOfRepo(c->redoAddress); i += 2) {
		char* address1 = getItemFromRepo(c->redoAddress, i);
		char* address2 = getItemFromRepo(c->redoAddress, i + 1);
		printf("\n%s %s", address1, address2);
		free(address2);
		free(address1);
	}
}*/