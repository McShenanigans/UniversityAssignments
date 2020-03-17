#pragma once
#include "exceptions.h"
#include <iostream>
#include <vector>

using namespace std;
template <typename TElem>
class repository
{
protected:
	string fileType;
    vector<TElem> v;
    int pos;
public:
	// repository constructor
    repository();
	
	// initializes a repository with a given fileType
	// input: a string containing the path to the file
	repository(string fileType);

	// returns the output file of the repository
	string getOutputFile();

	// adds a new item to the repo's array
	// input: the item
	// output: true if the operation was succceful; false otherwise
    void addEntry(const TElem& item);
    
	// reomves an item from the repo's array
	// input: the item
	// output: true if the operation was succceful; false otherwise
	void removeEntry(const int index);

	// writes the given input to a the repository's file
	// input: an array of strings containing a dog's property
	virtual void writeToFile(vector<string> items) = 0;

	virtual string lastOperation() = 0;
	virtual TElem lastObj() = 0;
	virtual void emptyRepo() = 0;
	virtual void pushOperation( string op, TElem obj) = 0;

	// checks if the repo's position field has exceeded the maximum size
	// output: true if it is the case; false otherwise
    bool isValid();

	// modifies one of the repo's items
	// input: the item's id, the field to update, the new value of that field
	void editEntry(const int index, TElem item);
    
	// incremnt the repo's positon field
	void next();

	// resets the repo's position field to 0
    void reset();

	// returns the size of the repo
    int getRepoSize();

	// returns the item located at a given index in the repo's array
	// input: the index
    TElem& getItem(int index);

	// returns the item located at the repo's position field in the repo's array
    TElem& getCurrentItem();

	// repository destructor
    virtual ~repository() {};
};

template <typename TElem>
repository<TElem>::repository()
{
    this->pos = 0;
}
template<typename TElem>
inline repository<TElem>::repository(string fileType){
	this->pos = 0;
	this->fileType = fileType;
}
template<typename TElem>
inline string repository<TElem>::getOutputFile(){
	return this->fileType;
}
template<typename TElem>
inline void repository<TElem>::addEntry(const TElem& item)
{
	for (auto &dog : this->v) {
		if (item == dog)throw myException("item already exists");
	}
    this->v.push_back(item);
}

template<typename TElem>
inline void repository<TElem>::removeEntry(const int index)
{
	if (index >= this->v.size() || index < 0) throw myException("item does not exist");
	for (int i = index; i < this->v.size() - 1; i++) {
		this->v[i] = this->v[i + 1];
	}
	this->v.pop_back(); 
}

template<typename TElem>
inline bool repository<TElem>::isValid()
{
    return this->pos < this->v.size();
}

template<typename TElem>
inline void repository<TElem>::editEntry(const int index, TElem item)
{
	if (index >= this->v.size() || index < 0) throw myException("index out of range");
	this->v[index] = item;
}

template<typename TElem>
inline void repository<TElem>::next()
{
    this->pos++;
}

template<typename TElem>
inline int repository<TElem>::getRepoSize()
{
    return this->v.size();
}

template<typename TElem>
inline TElem& repository<TElem>::getItem(int index)
{
    return this->v[index];
}

template<typename TElem>
inline TElem& repository<TElem>::getCurrentItem()
{
	if (this->pos >= this->v.size() || this->pos < 0) throw myException("index out of range");
    return this->v[this->pos];
}

template<typename TElem>
void repository<TElem>::reset() {
    this->pos = 0;    
}
