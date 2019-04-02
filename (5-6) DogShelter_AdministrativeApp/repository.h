#pragma once
#include "DynamicArray.h"
#include <iostream>

using namespace std;
template <typename TElem>
class repository
{
private:
    DynamicArray<TElem> vector;
    int pos;
public:
	// repository constructor
    repository();

	// adds a new item to the repo's array
	// input: the item
	// output: true if the operation was succceful; false otherwise
    bool addEntry(const TElem& item);
    
	// reomves an item from the repo's array
	// input: the item
	// output: true if the operation was succceful; false otherwise
	bool removeEntry(const int id);

	// checks if the repo's position field has exceeded the maximum size
	// output: true if it is the case; false otherwise
    bool isValid();

	// modifies one of the repo's items
	// input: the item's id, the field to update, the new value of that field
    void editEntry(const int id, const int field, const string newValue);
    
	// incremnt the repo's positon field
	void next();

	// resets the repo's position field to 0
    void reset();

	// returns the size of the repo
    int getRepoSize();

	// returns the item located at a given index in the repo's array
	// input: the index
    TElem getItem(int index);

	// returns the item located at the repo's position field in the repo's array
    TElem getCurrentItem();

	// repository destructor
    ~repository() {
        //cout << "\ndeinstantiated repo";
    };
};

template <typename TElem>
repository<TElem>::repository()
{
    this->pos = 0;
    //cout << "\ninstantiated repo";
}
template<typename TElem>
inline bool repository<TElem>::addEntry(const TElem& item)
{
    return this->vector.add(item);
}

template<typename TElem>
inline bool repository<TElem>::removeEntry(const int id)
{
    return this->vector.remove(id);
}

template<typename TElem>
inline bool repository<TElem>::isValid()
{
    return this->pos < this->vector.getSize();
}

template<typename TElem>
inline void repository<TElem>::editEntry(const int id, const int field, const string newValue)
{
    this->vector.editEntry(id, field, newValue);
}

template<typename TElem>
inline void repository<TElem>::next()
{
    this->pos++;
}

template<typename TElem>
inline int repository<TElem>::getRepoSize()
{
    return this->vector.getSize();
}

template<typename TElem>
inline TElem repository<TElem>::getItem(int index)
{
    return this->vector[index];
}

template<typename TElem>
inline TElem repository<TElem>::getCurrentItem()
{
    return this->vector[this->pos];
}

template<typename TElem>
void repository<TElem>::reset() {
    this->pos = 0;
}
