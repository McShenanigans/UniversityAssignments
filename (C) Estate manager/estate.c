#include "estate.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// creates a new object of type object
// input: the estate's type, address, price and surface
// output: a pointer towards the new estate
Estate* createEstate(char* type, char* address, int price, int surface) {
	Estate* estate = malloc(sizeof(Estate));
	
	estate->surface = surface;
	estate->price = price;

	estate->address = malloc(strlen(address) + 1);
	strcpy(estate->address, address);

	estate->type = malloc(strlen(type) + 1);
	strcpy(estate->type, type);
	
	return estate;
}

// frees the memory from an estate
// input: the estate
void destroyEstate(Estate* estate) {
	free(estate->type);
	free(estate->address);
	free(estate);
}

// copies an estate
// input: the estate to copy
// output: the copy of the estate
Estate* copyEstate(Estate* estate) {
	Estate* copy = malloc(sizeof(Estate));

	copy->surface = estate->surface;
	copy->price = estate->price;

	copy->address = malloc(strlen(estate->address) + 1);
	strcpy(copy->address, estate->address);

	copy->type = malloc(strlen(estate->type) + 1);
	strcpy(copy->type, estate->type);

	return copy;
}

// checks if 2 estates are equal
// input: the 2 estate pointer
// output: 1 if they are equal; 0 otherwise
int equalEstates(Estate* e1, Estate* e2) {
	return strcmp(e1->address, e2->address);
}

// modifies the address of an estate
// input: the estate
void setAddress(Estate* e, char* newValue) {
	free(e->address);
	e->address = malloc(strlen(newValue) + 1);
	strcpy(e->address, newValue);
}

// modifies the type of an estate
// input: the estate
void setType(Estate* e, char* newValue) {
	free(e->type);
	e->type = malloc(strlen(newValue) + 1);
	strcpy(e->type, newValue);
}

// modifies the price of an estate
// input: the estate
void setPrice(Estate* e, int price) {
	e->price = price;
}

// modifies the surface of an estate
// input: the estate
void setSurface(Estate* e, int surface) {
	e->surface = surface;
}

// converts an estate to a string
// input: the estate
char* estateToString(Estate* estate) {
	char* str = malloc(sizeof(char) * 300);
	sprintf(str, "type: %s; address: %s; price: %d; surface: %d\n", estate->type, estate->address, estate->price, estate->surface);
	return str;
}