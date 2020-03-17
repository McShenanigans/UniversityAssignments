#pragma once
#include "repository.h"
#include "estate.h"

typedef struct {
	Repository* repo;
	Repository* undoOps;
	Repository* undoObj;
	Repository* redoOps;
	Repository* redoObj;
	Repository* undoAddress;
	Repository* redoAddress;
}Controller;

Controller* createController();

void destroyController(Controller*);
void updateEntry(Controller*, char*, int, char*, int);
void undo(Controller*);
void redo(Controller*);
//void printUR(Controller*);

int newEntry(Controller*, char*, char*, int, int, int);
int dropEntry(Controller*, char*);
int getSize(Controller*);
int searchForMatches(Controller*, int*, char*);
int searchBySurface(Controller*, int*, int);
int searchByTypeSurface(Controller*, int*, char*, int);

char* getEstateString(Controller*, int);