#include "Dog.h"
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
Dog::Dog(){ 
	this->id = -1;
	this->age = -1;
}
Dog::Dog(int id, string name, string breed, int age, string photo) {
    this->id = id;
    this->name = name;
    this->breed = breed;
    this->age = age;
    this->photoLink = photo;
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

string Dog::dogStringSimple() const {
	string id = intToString(this->id);
	string age = intToString(this->age);
	return id + "," + this->name + "," + this->breed + "," + age + "," + this->photoLink;
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

bool Dog::valid()
{
	return !(this->id == -1 || this->age == -1);
}

vector<string> createFormat(string str, char delimiter) {
	vector<string> format;
	stringstream ss(str);
	string attr;
	while (getline(ss, attr, delimiter)) {
		format.push_back(attr);
	}
	return format;
}

ostream & operator<<(ostream & os, Dog & d) {
	os << d.getID() << "," << d.getName() << "," << d.getBreed() << "," << d.getAge() << "," << d.getPhoto()<<"\n";
	return os;
}

istream & operator>>(istream & is, Dog & d)
{
	string line;
	getline(is, line);
	vector<string> attrs = createFormat(line, ',');
	if (attrs.size() != 5) return is;
	d.id = stoi(attrs[0]);
	d.name = attrs[1];
	d.breed = attrs[2];
	d.age = stoi(attrs[3]);
	d.photoLink = attrs[4];
	return is;
}
