#include "ui.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// prints the list of available commands
void showMenu() {
	printf("\nChoose an action:\n\t0 - exit program\n\t1 - add estate\n\t2 - remove estate\n\t3 - update estate\n\t4 - search for estates\n\t5 - search by surface\n\t6 - search by surface in a given type\t\n\t7 - undo\n\t8 - redo\n>>> ");
}

// checks if a string is a number
// input: a string
// output: 1 for True or 0 for False
int isnumber(char input[]) {
	int len = strlen(input), i, count = 0;
	for (i = 0; i < len; i++) {
		if (input[i] > 47 && input[i] < 58) {
			count++;
		}
	}
	if (count != len - 1) {
		return 0;
	}
	return 1;
}

// reads the user's input for the main menu
// output: an integer representing the the desired command
int readInput() {
	char* input = malloc(sizeof(char)*256);
	int i, j;
	fgets(input, sizeof(input), stdin);
	if (isnumber(input) == 1) {
		i = atoi(input);
		for (j = 0; j < 9; j++) {
			if (i == j) {
				free(input);
				return i;
			}
		}
	}
	printf("\nINVALID INPUT!\n");
	free(input);
	return -1;
}

// reads the type of an estate
// output: a string containing the estate's type; NULL for invalid types
char* readType() {
	char* input = malloc(256 * sizeof(char));
	printf("Enter the type of the estate (lowercase letters only)\n>>> ");
	fgets(input, 256, stdin);
	input[strlen(input) - 1] = 0;
	if (strcmp(input, "house") == 0 || strcmp(input, "penthouse") == 0 || strcmp(input, "apartment") == 0) {
		return input;
	}
	printf("\nERROR! INAPPROPRIATE ESTATE TYPE OR UPPERCASE LETTERS!\n");
	free(input);
	return NULL;
}

// reads the address of an estate
// output: a string containing the input
char* readAddress() {
	char* address = malloc(256 * sizeof(char));
	printf("Enter the address of the estate\n>>> ");
	fgets(address, 256, stdin);
	address[strlen(address) - 1] = 0;
	return address;
}

// reads the price of an estate
// output: a string containing a number; NULL if the input is not a number
char* readPrice() {
	int price;
	char* input = malloc(10 * sizeof(char));
	printf("Enter the price of the estate.\n>>> ");
	fgets(input, 10, stdin);
	input[strlen(input) - 1] = 0;
	if (isnumber(input) == 0) {
		return input;
	}
	printf("\nERROR! INPUT MUST BE A POSITIVE INTERGER!\n");
	free(input);
	return NULL;
}

// reads the surface of an estate
// output: a string containing a number; NULL if the input is not a number
char* readSurface() {
	int price;
	char* input = malloc(10 * sizeof(char));
	printf("Enter the surface of the estate.\n>>> ");
	fgets(input, 10, stdin);
	input[strlen(input) - 1] = 0;
	if (isnumber(input) == 0) {
		return input;
	}
	printf("\nERROR! INPUT MUST BE A POSITIVE INTERGER!\n");
	free(input);
	return NULL;
}

// reads the field which the user wants to update
// output: an int coresponding to the field; -1 if the input is invalid
int whatToUpdate() {
	int objToUpdate;
	char* input = malloc(10 * sizeof(char));
	printf("What do you desire to update?\n\t1 - the type\n\t2 - the address\n\t3 - the price\n\t4 - the surface\n>>> ");
	fgets(input, 10, stdin);
	input[strlen(input) - 1] = 0;
	if (isnumber(input) == 0) {
		objToUpdate = atoi(input);
		free(input);
		if (objToUpdate < 5 && objToUpdate > 0) return objToUpdate;
		printf("\nERROR! INPUT OUT OF SPECIFIED RANGE! (1-4)\n");
		return -1;
	}
	printf("\nERROR! INVALID INPUT!\n");
	free(input);
	return -1;
}

// reads and returns a string
char* readStringToSearch() {
	char* string = malloc(256 * sizeof(char));
	printf("Enter what you want to search for.\n>>> ");
	fgets(string, 256, stdin);
	string[strlen(string) - 1] = 0;
	return string;
}

// notifies the user if the estate they want to add already exists
void estateAlreadyExists() {
	printf("\nERROR! THE ESTATE YOU WANT TO ADD ALREADY EXISTS!\n");
}

// notifies the user if the estate they want to remove does not exist
void estateNonExistent() {
	printf("\nERROR! THE ESTATE YOU WANT TO REMOVE DOES NOT EXISTS!\n");
}

// prints a string containing an estate's data
// input: the string
void printEstate(char* string) {
	printf("%s", string);
	free(string);
}