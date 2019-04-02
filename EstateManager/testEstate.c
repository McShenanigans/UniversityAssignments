#include "testEstater.h"
#include "estate.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>

void testEstate() {
	Estate* estate1 = createEstate("a", "address", 500, 50);

	//test copyEstate
	Estate* estate2 = copyEstate(estate1);
	assert(strcmp(estate1->type, estate2->type) == 0);
	assert(strcmp(estate1->address, estate2->address) == 0);
	assert(estate1->price == estate2->price);
	assert(estate1->surface == estate2->surface);
	destroyEstate(estate2);

	//test equalEstates
	estate2 = createEstate("b", "address", 560, 56);
	assert(equalEstates(estate1, estate2) == 0);
	destroyEstate(estate2);

	// tests estateToString
	char* str1 = estateToString(estate1);
	char* str2 = "type: a; address: address; price: 500; surface: 50\n";
	assert(strcmp(str1, str2) == 0);
	free(str2);
	free(str1);

	// test setAddress
	setAddress(estate1, "address1");
	assert(strcmp(estate1->address, "address1") == 0);

	// test setType
	setType(estate1, "address1");
	assert(strcmp(estate1->type, "address1") == 0);
	
	// test setPrice
	setPrice(estate1, 560);
	assert(estate1->price == 560);
	
	// test setSurface
	setSurface(estate1, 56);
	assert(estate1->surface == 56);
	
	destroyEstate(estate1);
}