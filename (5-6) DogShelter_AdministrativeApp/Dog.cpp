#include "Dog.h"
#include <iostream>
using namespace std;
Dog::Dog(){ 
	//cout << "\ninstantiated dog";
}
Dog::Dog(int id, string name, string breed, int age, string photo) {
    this->id = id;
    this->name = name;
    this->breed = breed;
    this->age = age;
    this->photoLink = photo;
    //cout << "\ninstantiated dog with params";
}

string Dog::getName() const {
    return this->name;
}

string Dog::getBreed() const {
    return this->breed;
}

int Dog::getAge() const {
    return this->age;
}

string Dog::getPhoto() const {
    return this->photoLink;
}

string Dog::dogString() const
{
    string id = intToString(this->id);
    string age = intToString(this->age);
    return id + ". " + this->name + ": breed - " + this->breed + "; age - " + age + "; photoLink - " + this->photoLink;
}

int Dog::getID() const {
    return this->id;
}

void Dog::setAge(int newAge) {
    this->age = newAge;
}

void Dog::setBreed(string newBreed) {
    this->breed = newBreed;
}

void Dog::setName(string newName) {
    this->name = newName;
}

void Dog::setPhoto(string newPhoto) {
    this->photoLink = newPhoto;
}