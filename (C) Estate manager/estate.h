#pragma once

typedef struct {
	char* type; char *address;
	int price; int surface;
}Estate;

Estate* createEstate(char*, char*, int, int);
Estate* copyEstate(Estate*);

int equalEstates(Estate*, Estate*);

void destroyEstate(Estate*);
void setAddress(Estate*, char*);
void setType(Estate*, char*);
void setPrice(Estate*, int);
void setSurface(Estate*, int);

char* estateToString(Estate*);