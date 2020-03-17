#pragma once
#include <string>

using namespace std;

// checks if an item is in a list
// input: the item, the list, the list's length
// output: true if the item was found; false otherwise
bool inList(int item, int* list, int len);

// convert an int into a string
// input: the int
// output: a string representing the int
string intToString(int n);
