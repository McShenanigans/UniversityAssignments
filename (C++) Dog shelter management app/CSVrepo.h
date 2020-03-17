#pragma once
#include "repository.h"
template <typename TElem>
class CSVrepo : public repository<TElem>
{
public:
	// initializes a CSVrepo
	CSVrepo();
	// destructor
	~CSVrepo() {};
	// writes the input to the dogs.csv file
	// input: an array of strings containing the each dog's data
	void writeToFile(vector<string> items) override;
	void pushOperation(string op, TElem obj) override;
	void emptyRepo() override;
	string lastOperation() override;
	TElem lastObj() override;
};

template<typename TElem>
inline CSVrepo<TElem>::CSVrepo() : repository<TElem>{ "dogs.csv" } {}

template<typename TElem>
inline void CSVrepo<TElem>::writeToFile(vector<string> items){
	ofstream f(this->fileType, ios::trunc);
	for (string item : items) {
		f << item+"\n";
	}
	f.close();
}

template<typename TElem>
inline void CSVrepo<TElem>::pushOperation(string op, TElem obj) {}

template<typename TElem>
inline void CSVrepo<TElem>::emptyRepo() {}

template<typename TElem>
inline string CSVrepo<TElem>::lastOperation() { return string(); }

template<typename TElem>
inline TElem CSVrepo<TElem>::lastObj() { return TElem(); }
