#include "generalTools.h"
using namespace std;
bool inList(int item, int *list, int len) {
	for (int i = 0; i < len; i++) {
		if (item == list[i]) return true;
	}
	return false;
}

string intToString(int n) {
	char result[10];
	int rev = 0, zeros = 0;
	do {
		if (rev == 0 && n % 10 == 0) zeros++;
		rev = rev * 10 + n % 10;
		n /= 10;
	} while (n);
	int i = 0;
	while (rev) {
		result[i] = rev % 10 + 48;
		rev /= 10;
		i++;
	}
	while (zeros) {
		result[i] = 48;
		i++;
		zeros--;
	}
	result[i] = 0;
	return result;
}