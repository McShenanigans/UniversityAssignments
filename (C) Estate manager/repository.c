#include "repository.h"

// creates a repository object
// input: a function to destroy an item from the repo, one to check if 2 items are equal and one to copy an item
// output: the repo
Repository* createRepo(void(*destroy)(TElem), int(*equal)(TElem, TElem), TElem(*copy)(TElem)) {
	Repository* repo = malloc(sizeof(Repository));
	repo->copy = copy;
	repo->destroy = destroy;
	repo->equal = equal;
	repo->list = createDynamicArray(2);
	return repo;
}

// free the heap of a repository
// input: the repo
void destroyRepo(Repository* repo) {
	destroyDynamicArray(repo->list, repo->destroy);
	free(repo);
}

// add an entry into a repository
// input: the repo, the item to add, a flag for undo/redo
// input: 1 for succesful operation; 0 otherwise
int addEntry(Repository* repo, TElem item, int flag) {
	TElem elem = searchDynamicArray(repo->list, item, repo->equal, repo->copy);
	if (elem == NULL || flag == 1) {
		addItem(repo->list, item, repo->copy);
		if (elem != NULL) {
			repo->destroy(elem);
		}
		return 1;
	}
	else {
		repo->destroy(elem);
		return 0;
	}
}

// add an entry into a repository
// input: the repo, the item to add
// input: 1 for succesful operation; 0 otherwise
int removeEntry(Repository* repo, TElem item) {
	TElem elem = searchDynamicArray(repo->list, item, repo->equal, repo->copy);
	if (elem == NULL) {
		return 0;
	}
	else {
		repo->destroy(elem);
		removeItem(repo->list, item, repo->equal, repo->destroy);
		return 1;
	}
}

// removes the last added item from a repo
// input: the repo
void removeLastEntry(Repository* repo) {
	removeLastItem(repo->list, repo->destroy);
}

// returns a copy of an item from a repo
// input: the repo, the item
// output: a copy if the item was found, NULL otherwise
TElem searchRepo(Repository* repo, TElem item) {
	return searchDynamicArray(repo->list, item, repo->equal, repo->copy);
}

// returns a copy of the item from a repo located at a given index
// input: the repo, the index
// output: a copy of the item if it was found, NULL otherwise
TElem getItemFromRepo(Repository* repo, int index) {
	return getItem(repo->list, index, repo->copy);
}

// returns the number of entries in a repo
// input: the repo
int getSizeOfRepo(Repository* repo) {
	return getDynamicArraySize(repo->list);
}