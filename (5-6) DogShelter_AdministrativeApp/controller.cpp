#include "controller.h"
#include <iostream>

using namespace std;

controller::controller() {
    //cout << "\ninstantiated constroller";
}

bool controller::addDog(const string name, const string breed, const int age, const string photo) {
	int id = 0;
	if (this->repoSize() > 0) {
		id = this->dogs.getItem(this->dogs.getRepoSize() - 1).getID() + 1;
	}
    Dog newDog{id, name, breed, age, photo};
    return this->dogs.addEntry(newDog);
}

bool controller::removeDog(int id) {
    return this->dogs.removeEntry(id);
}

void controller::editDog(const int id, const int field, const string newValue) {
    this->dogs.editEntry(id, field, newValue);
}

int controller::repoSize() {
    return this->dogs.getRepoSize();
}

int controller::getDogs(const string breed, int *found) {
    int i = 0;
    if (breed.empty()) {
        this->dogs.reset();
        while (this->dogs.isValid()) {
            found[i] = this->dogs.getCurrentItem().getID();
            i++;
            this->dogs.next();
        }
        this->dogs.reset();
    } else {
        this->dogs.reset();
        while (this->dogs.isValid()) {
            if (this->dogs.getCurrentItem().getBreed() == breed) {
                found[i] = this->dogs.getCurrentItem().getID();
                i++;
            }
            this->dogs.next();
        }
        this->dogs.reset();
    }
    return i;
}

const string controller::getDogstring(int index) {
    return this->dogs.getItem(index).dogString();
}

const string controller::getDogstringID(int id) {
    for (int i = 0; i < this->repoSize(); i++) {
        if (this->dogs.getItem(i).getID() == id)
            return this->getDogstring(i);
    }
    return "";
}

const string controller::getLink(int id){
    for (int i = 0; i < this->repoSize(); i++) {
        if (this->dogs.getItem(i).getID() == id)
            return this->dogs.getItem(i).getPhoto();
    }
    return "https://www.youtube.com/watch?v=X7rAnaKId3E";
}
