#include "controller.h"
#include "tests.h"
#include "ui.h"
#include "generalTools.h"
#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

using namespace std;

// initializes the controller's repo with 10 values
void initialize(controller &c) {
    c.addDog("Doge", "Shiba-Inu", 7, "https://www.youtube.com/watch?v=Yj7ja6BANLM");
    c.addDog("Spike", "GermanShepard", 10, "https://www.youtube.com/watch?v=bfHYS-P--F0");
    c.addDog("Dave", "Labrador", 5, "https://www.youtube.com/watch?v=in_jF1W3jUg");
    c.addDog("Mishka", "Husky", 7, "https://www.youtube.com/watch?v=qXo3NFqkaRM");
    c.addDog("Jack", "GoldenRetriever", 1, "https://www.youtube.com/watch?v=a6KGPBflhiM");
    c.addDog("Mimi", "YorkshireTerrier", 4, "https://www.youtube.com/watch?v=yujntyRK2qA");
    c.addDog("Tom", "Akita-Inu", 6, "https://www.youtube.com/watch?v=RZ3zg5KiXsg");
    c.addDog("Scooby-Doo", "GreatDane", 50, "https://www.youtube.com/watch?v=776rvGHfzuM");
    c.addDog("Jerry", "Chihuahua", 3, "https://www.youtube.com/watch?v=7PLuhK82Xjs");
    c.addDog("Toro", "Doberman", 8, "https://www.youtube.com/watch?v=GCM0phNqL0g");
}

// manages an admin sesion
void adminMode(controller &c) {
    int cmd;
    while (true) {
        cmd = readAdminInput();
        if (cmd == 0) {
            break;
        } else if (cmd == 1) {
            string name = readAttribute("name");
            string breed = readAttribute("breed");
            string photo = readAttribute("photography hyperlink");
            int age = readNumAtr("age");
            if (age != -1) {
                bool succesful = c.addDog(name, breed, age, photo);
                if (!succesful) printMsg("DOG ALREADY EXISTS!");
            }
        } else if (cmd == 2) {
            int id = readNumAtr("id");
            if (id != -1) {
                bool succesful = c.removeDog(id);
                if (!succesful) printMsg("DOG DOES NOT EXIST!");
            }
        } else if (cmd == 3) {
            int id = readNumAtr("id");
            if (id != -1) {
                int objToUpdate = whatToUpdate();
                if (objToUpdate != -1) {
                    string obj;
                    if (objToUpdate == 1) obj = readAttribute("new name");
                    if (objToUpdate == 2) obj = readAttribute("new breed");
                    if (objToUpdate == 3) {
                        int age = readNumAtr("new age");
                        if (age != -1) obj = intToString(age);
                        else obj = "";
                    }
                    if (objToUpdate == 4) obj = readAttribute("new photo");
                    if (obj == "" && objToUpdate == 3);
                    else c.editDog(id, objToUpdate, obj);
                }
            }
        } else if (cmd == 4) {
            for (int i = 0; i < c.repoSize(); i++) {
                printMsg(c.getDogstring(i));
            }
        }
    }
}

// manages a guest sesion
// input: a controler, an integer value for the length of the adoptionList
// output: the list of dogs that the user wnats to adopt
int *guestMode(controller &c, int &len) {
    int *adoptionList = new int[c.repoSize()];
    int number = 0;
    int cmd;
    while (true) {
        cmd = readGuestInput();
        if (cmd == 0) {
            break;
        } else if (cmd == 1) {
            int *found = new int[c.repoSize()];
            int len = c.getDogs("", found);
            for (int i = 0; i < len; i++) {
                if (!inList(found[i], adoptionList, number)) {
                    printMsg(c.getDogstringID(found[i]));
                    int input = adoptQ();
                    if (input == 4) break;
                    else if (input == 1) {
                        adoptionList[number++] = found[i];
					}
					else if (input == 3) {
						openLink(c.getLink(found[i]));
						i--;
					}
                }
                if (i == len - 1) i = -1;
            }
            delete[] found;
        } else if (cmd == 2) {
            int *found = new int[c.repoSize()];
            string breed = readAttribute("breed");
            int len = c.getDogs(breed, found);
            for (int i = 0; i < len; i++) {
                if (!inList(found[i], adoptionList, number)) {
                    printMsg(c.getDogstringID(found[i]));
                    int input = adoptQ();
                    if (input == 3) break;
                    else if (input == 1) {
                        adoptionList[number++] = found[i];
                    }
                }
                if (i == len - 1) i = -1;
            }
            delete[] found;
        } else if (cmd == 3) {
            for (int i = 0; i < number; i++) {
                printMsg(c.getDogstringID(adoptionList[i]));
            }
        }
    }
    len = number;
    return adoptionList;
}

// manages acocunt selection
int runProgram(){
	{
		controller c;
		initialize(c);
		int input = -1;
		while (input == -1) {
			input = readMode();
		}
		while (input) {
			if (input == 1) {
				adminMode(c);
			}
			else if (input == 2) {
				int len, in;
				int *adoptionList = guestMode(c, len);
				in = sureAdopt();
				if (in == 1) {
					for (int i = 0; i < len; i++) {
						c.removeDog(adoptionList[i]);
					}
				}
				delete[] adoptionList;
			}
			input = -1;
			while (input == -1) {
				input = readMode();
			}
		}
	}
	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}

int main() {
	runProgram();
	testAll();
}