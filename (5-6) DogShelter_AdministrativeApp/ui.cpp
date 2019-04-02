#include "ui.h"
#include <Windows.h>
#include <shellapi.h>
#include <string>
#include <iostream>
using namespace std;

// clears the cin buffer after inputting multiple words
void emptyInputStack() {
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}

// checks if a string is a positive number
// input: the string
// output: true if the stirng is a number; false otherwise
bool isNumber(string str) {
    for (int i = 0; str[i] != 0; i++) {
        if (str[i]<'0' || str[i]>'9') return false;
    }
    return true;
}

int readMode()
{
    string input;
    cout << "Choose a mode:\n\t0 - exit\n\t1 - administrator mode\n\t2 - guest mode\n>>> ";
    cin >> input;
    emptyInputStack();
    if (isNumber(input)) {
        if (-1 < stoi(input) && stoi(input) < 3) return stoi(input);
        cout << "\nERROR! INVALID COMMAND!\n";
        return -1;
    }
    cout << "\nERROR! INVALID INPUT!\n";
    return -1;
}

int readAdminInput() {
    string input;
    cout << "Choose an action:\n\t0 - logout\n\t1 - add dog\n\t2 - remove dog\n\t3 - update dog\n\t4 - see all dogs\n>>> ";
    cin >> input;
    emptyInputStack();
    if (isNumber(input)) {
        if (-1 < stoi(input) && stoi(input) < 5) return stoi(input);
        cout << "\nERROR! INVALID COMMAND!\n";
        return -1;
    }
    cout << "\nERROR! INVALID INPUT!\n";
    return -1;
}

int readNumAtr(const string atr)
{
    string age;
    cout << "Please enter the dog's " + atr + ".>>> ";
    cin >> age;
    emptyInputStack();
    if (isNumber(age)) return stoi(age);
    cout << "\nERROR! " + atr + " MUST BE A POSITIVE INTEGER!\n";
    return -1;
}

const string readAttribute(const string atr)
{
    string input = "", word = "a";
    cout << "Please enter the dog's " + atr + ".>>> ";
    cin >> input;
    emptyInputStack();
    return input;
}

void openLink(string link)
{
	ShellExecute(NULL, NULL, "chrome.exe", link.c_str(), NULL, SW_SHOWMAXIMIZED);
}

void printMsg(const string obj) {
    cout << "\n" << obj << "\n";
}

int whatToUpdate() {
    string input;
    cout << "Choose the attribute you want to update:\n\t1 - the name\n\t2 - the breed\n\t3 - the age\n\t4 - the photo\n>>> ";
    cin >> input;
    emptyInputStack();
    if (isNumber(input)) {
        if (0 < stoi(input) && stoi(input) < 5) return stoi(input);
        cout << "\nERROR! INVALID COMMAND\n";
        return -1;
    }
    cout << "\nERROR! INVALID INPUT!\n";
    return -1;
}

int readGuestInput() {
    string input;
    cout << "Choose an action:\n\t0 - logout\n\t1 - see all dogs\n\t2 - see dogs by breed\n\t3 - see adoption list\n>>> ";
    cin >> input;
    emptyInputStack();
    if (isNumber(input)) {
        if (-1 < stoi(input) && stoi(input) < 4) return stoi(input);
        cout << "\nERROR! INVALID COMMAND!\n";
        return -1;
    }
    cout << "\nERROR! INVALID INPUT!\n";
    return -1;
}

int adoptQ(){
    string input;
    cout << "Do you wish to adopt this dog?\n\t1 - YES!!!\n\t2 - OH GOD! NO!\n\t3 - open photo in browser\n\t4 - quit browsing\n>>> ";
    cin >> input;
    emptyInputStack();
    if(isNumber(input)){
        if (0<stoi(input) && 5>stoi(input)) return stoi(input);
        cout << "\nERROR! INVALID COMMAND\n";
        return -1;
    }
    cout <<"\nERROR! INVALID INPUT!\n";
    return -1;
}

int sureAdopt(){
    string input;
    cout << "All the dogs you chose to adopt will be adopted. Proceed?\n\t1 - YES!!!\n\t2 - OH GOD! NO!\n>>> ";
    cin >> input;
    emptyInputStack();
    if(isNumber(input)){
        if (0<stoi(input) && 3>stoi(input)) return stoi(input);
        cout << "\nERROR! INVALID COMMAND! NONE OF THE DOGS YOU SELECTED WILL BE ADOPTED :(\n";
        return -1;
    }
    cout <<"\nERROR! INVALID INPUT! NONE OF THE SELECTED DOGS WILL BE ADOPTED :(\n";
    return -1;
}