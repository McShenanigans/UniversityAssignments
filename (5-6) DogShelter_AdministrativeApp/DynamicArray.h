#pragma once
#include <string>
#include <iostream>
using namespace std;

template <typename TElem>
class DynamicArray {
private:
    int size, cap;
    TElem* elems;

public:
	// array constructor
    DynamicArray();

	// array destructor
    ~DynamicArray();

	// returns the size of the array
    const int getSize();

	// adds an item to the array
	// input: the item to add
	// output: true if the operation was succesful; false otherwise
    bool add(const TElem& item);
    
	// removes an item to the array
	// input: the item to remove
	// output: true if the operation was succesful; false otherwise
	bool remove(const int id);

	// modifies one of an item's attributes
	// input: the item's id, the attribute to update, the new value of the attribute
    bool editEntry(const int id, const int field, const string newValue);

	// returns the item located at a given position
	// input: the position of the desired item
    TElem operator[](int pos) {
        return this->elems[pos];
    }

private:

	// resizes the array if the cap is reached
    void resize();
};

template <typename TElem>
DynamicArray<TElem>::DynamicArray() {
    this->size = 0;
    this->cap = 2;
    this->elems = new TElem[2];
    //cout << "\ninstantiated dynamic array";
}

template <typename TElem>
DynamicArray<TElem>::~DynamicArray() {
    //cout << "\ndeinstantiated dynamic array";
    delete[] this->elems;
}

template<typename TElem>
inline const int DynamicArray<TElem>::getSize()
{
    return this->size;
}

template <typename TElem>
inline bool DynamicArray<TElem>::add(const TElem& item) {
    for (int i = 0; i < this->size; i++) {
        if (this->elems[i] == item) return false;
    }
    resize();
    this->elems[this->size] = item;
    this->size++;
    return true;
}

template <typename TElem>
inline bool DynamicArray<TElem>::remove(const int id) {
    for (int i = 0; i < this->size; i++) {
        if (this->elems[i].getID() == id) {
            for (int j = i; j < this->size - 1; j++) {
                this->elems[j] = this->elems[j + 1];
            }
            this->size--;
            return true;
        }
    }
    return false;
}

template <typename TElem>
inline bool DynamicArray<TElem>::editEntry(const int id, const int field, const string newValue) {
    for (int i = 0; i < this->size; i++) {
        if (this->elems[i].getID() == id) {
            if (field == 1) this->elems[i].setName(newValue);
            else if (field == 2) this->elems[i].setBreed(newValue);
            else if (field == 4) this->elems[i].setPhoto(newValue);
            else if (field == 3) this->elems[i].setAge(stoi(newValue));
			return true;
        }
    }
	return false;
}

template <typename TElem>
inline void DynamicArray<TElem>::resize() {
    if (this->size == this->cap) {
        TElem* newArray = new TElem[this->cap * 2];
        for (int i = 0; i < this->size; i++) {
            newArray[i] = this->elems[i];
        }
        delete[] this->elems;
        this->elems = newArray;
        this->cap *= 2;
    }
}