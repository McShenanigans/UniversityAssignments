#pragma once
#include "CSVrepo.h"
#include "HTMLrepo.h"
#include "UndoRepo.h"
#include "Dog.h"
#include "repository.h"
#include "dogValidator.h"
#include <iostream>
#include <Windows.h>
#include <shellapi.h>
using namespace std;
class controller
{
private:
    repository<Dog>* dogs;
	repository<Dog>* undoRepo;
	repository<Dog>* redoRepo;
public:
	// controller constructor
    controller(int fileType);

	// adds a dog to the controller's repo
	// input: the dog's name, breed, age and a link towards a photo of the dog
    // output: true if the operation was succesful; false otherwise
	bool addDog(const string name, const string breed, const int age, const string photo, bool fromInit = false);

	//removes a dog from the controller's repo
	// input: the dog's id
	// output: true if the operation was succesful; false otherwise
    bool removeDog(const int id);

	// modifies one of the attributes of a dog
	// input: the dog's id, the attribute to update, the new value of the attribute
    void editDog(const int id, const int field, const string newValue);

	// saves the current state of the dogs repository to the specified file and the default one
	void saveChanges();

	// opens the file specified at the start of the program in the adequate application
	void openFile();
	
	// reads the data from the default save file and adds the valid objects to the dogs repository
	void initializeC();

	bool undo();
	bool redo();

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

	const string getDogName(int index) const;
	const string getDogBreed(int index) const;
	const string getDogLink(int index) const;
	const int getDogAge(int index) const;
	const int getDogID(int index) const;
    
	// return the link of the dog with a given id
	// input: the dog's id
	const string getLink(int id);
	const int getIndex(int id);

	// controller destructor
	~controller();
};

