#pragma once
#include "Dog.h"
#include "repository.h"
#include <iostream>
using namespace std;
class controller
{
private:
    repository<Dog> dogs;
public:
	// controller constructor
    controller();

	// adds a dog to the controller's repo
	// input: the dog's name, breed, age and a link towards a photo of the dog
    // output: true if the operation was succesful; false otherwise
	bool addDog(const string name, const string breed, const int age, const string photo);

	//removes a dog from the controller's repo
	// input: the dog's id
	// output: true if the operation was succesful; false otherwise
    bool removeDog(const int id);

	// modifies one of the attributes of a dog
	// input: the dog's id, the attribute to update, the new value of the attribute
    void editDog(const int id, const int field, const string newValue);

	// returns the size of the constroller's repo
    int repoSize();

	// creates a list of the ids of the dogs with the given breed
	// input: the breed, the array to add the ids to;
	// output: the number of results
    int getDogs(const string breed, int* found);

	// return a string of the dog located at the given index in the controller's repo
	// input: the dog's index
    const string getDogstring(int index);

	// returns a string of the dog with the given id
	// input: the id;
    const string getDogstringID(int id);
    
	// return the link of the dog with a given id
	// input: the dog's id
	const string getLink(int id);

	// controller destructor
    ~controller() {
        //cout << "\ndeinstantiated controller";
    };
};

