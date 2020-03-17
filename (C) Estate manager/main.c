#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <Windows.h>
#include "ui.h"
#include "controller.h"

// intializes the controller with 10 items
void initialize(Controller* c) {
		newEntry(c, "house", "address10", 579, 125, 0);
		newEntry(c, "house", "address42", 500, 100, 0);
		newEntry(c, "penthouse", "address69", 400, 40, 0);
		newEntry(c, "penthouse", "address56", 2100, 180, 0);
		newEntry(c, "penthouse", "address14", 769, 30, 0);
		newEntry(c, "penthouse", "address46", 516, 60, 0);
		newEntry(c, "apartment", "address79", 230, 40, 0);
		newEntry(c, "apartment", "address16", 510, 50, 0);
		newEntry(c, "apartment", "address60", 330, 36, 0);
		newEntry(c, "apartment", "address90", 2205, 250, 0);
	}

int main() {
	Controller* c = createController();
	char *type, *address, *newAddress, *price, *surface, *newValue = NULL;
	int *found = NULL;
	int result, input, objToUpdate, len;
	initialize(c);
	while (1) {
		//printUR(c);
		showMenu();
		input = readInput();
		if (input == 0) {
			destroyController(c);
			_CrtDumpMemoryLeaks();
			return 0;
		}
		else if (input == 1) {
			type = readType();
			if (type != NULL) {
				address = readAddress();
				price = readPrice();
				if (price != NULL) {
					surface = readSurface();
					if (surface != NULL) {
						result = newEntry(c, type, address, atoi(price), atoi(surface), 1);
						if (result == 0) estateAlreadyExists();
						free(surface);
					}
					free(price);
				}
				free(address);
				free(type);
			}
		}
		else if (input == 2) {
			address = readAddress();
			result = dropEntry(c, address);
			if (result == 0) estateNonExistent();
			free(address);
		}
		else if (input == 3) {
			address = readAddress();
			objToUpdate = whatToUpdate();
			if (objToUpdate == 1) {
				newValue = readType();
			}
			else if (objToUpdate == 2) {
				newValue = readAddress();
			}
			else if (objToUpdate == 3) {
				newValue = readPrice();
			}
			else if (objToUpdate == 4) {
				newValue = readSurface();
			}
			if (newValue != NULL) {
				updateEntry(c, address, objToUpdate, newValue, 0);
				free(newValue);
			}
			free(address);
		}
		else if (input == 4) {
			found = malloc(getSize(c) * sizeof(int));
			newValue = readStringToSearch();

			len = searchForMatches(c, found, newValue);
			for (result = 0; result < len; result++) {
				printEstate(getEstateString(c, found[result]));
			}

			free(newValue);
			free(found);
		}
		else if (input == 5) {
			surface = readSurface();
			if (surface != NULL) {
				found = malloc(getSize(c) * sizeof(int));
				len = searchBySurface(c, found, atoi(surface));
				for (result = 0; result < len; result++) {
					printEstate(getEstateString(c, found[result]));
				}
				free(found);
				free(surface);
			}
		}
		else if (input == 6) {
			type = readType();
			if (type != NULL) {
				surface = readSurface();
				if (surface != NULL) {
					found = malloc(getSize(c) * sizeof(int));
					len = searchByTypeSurface(c, found, type, atoi(surface));
					for (result = 0; result < len; result++) {
						printEstate(getEstateString(c, found[result]));
					}
					free(found);
					free(surface);
				}
				free(type);
			}
		}
		else if (input == 7) {
			undo(c);
		}
		else if (input == 8) {
			redo(c);
		}
	}
}