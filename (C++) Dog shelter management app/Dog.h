#pragma once
#include <string>
#include "generalTools.h"
#include <iostream>
using namespace std;
class Dog
{
protected:
    string name, breed, photoLink;
    int age, id;
public:
	// generic dog constructor
    Dog();

	// custom dog contructor
	// input: the dog's name, breed, age and a link towards a photo of the dog
    Dog(int id, string name, string breed, int age, string photo);

	// dog destructor
    ~Dog() {};

	// return the name of the dog
    string getName() const;
    
	// return the breed of the dog
	string getBreed() const;

	// return the link for the dog's photo
    string getPhoto() const;

	// returns a simple version of dogString
	string dogStringSimple() const;

	// return a string containing the dog's info
    string dogString() const;

	// return the age of the dog
    int getAge() const;

	// return the od of the dog
    int getID() const;

	// sets the dog's age to a new value
    void setAge(int newAge);

	// sets the dog's breed to a new value
    void setBreed(string newBreed);

	// sets the dog's name to a new value
    void setName(string newName);

	// sets the dog's photo to a new value
    void setPhoto(string newPhoto);

	// checks if the object is a valid dog
	// returns true if it is and false otherwise
	bool valid();

	// compares two dogs to each another
	// input: the 2 dogs
	// output: true if the dogs are the same; false otherwise
    friend bool operator==(const Dog& dog1, const Dog& dog2) {
        return dog1.id == dog2.id || dog1.name == dog2.name;
    }

	// operator for outputting the dog to a txt/csv file
	friend ostream& operator<<(ostream& os, Dog& d);

	// operator for reading the dog from a txt/csv file
	friend istream& operator>>(istream& is, Dog& d);
};