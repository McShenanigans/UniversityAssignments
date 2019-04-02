#pragma once
#include <string>
using namespace std;

// reads the mode in which the user wants to use the program
// output: 1 - admin mode; 2 - guest mode; -1 = invalid input
int readMode();

// reads the command the admin wants to use
// output: the command's id
int readAdminInput();

// reads the command the guest wants to use
// output: the command's id
int readGuestInput();

// reads a numeric value for creating an object
// input: the object's type as a string
// output: a positive int repersenting the value; -1 - invalid input
int readNumAtr(string atr);

// reads the field the user wnats to update
// output: the field's id (int); -1 - invalid input
int whatToUpdate();

// reads the guest's command while viewing the dogs
// output: 1 - adopt; 2 - skip dog; 3 - exit viewing mode; -1 - invalid input
int adoptQ();

// notifies the user that they are about to adopt the dogs they slected
// output: 1 - accept; 2 - decline; -1 = invalid input
int sureAdopt();

// reads the value of a string-type item and returns the value
// input: the item's type as a string
const string readAttribute(const string atr);

// opens the given link in the default browser
void openLink(string link);

// print a messege
void printMsg(string obj);