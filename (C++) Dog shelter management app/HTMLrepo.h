#pragma once
#include "repository.h"
#include <sstream>
template <typename TElem>
class HTMLrepo : public repository<TElem>
{
private:
	vector<string> createFormat(string str, char delimiter);
public:
	// creates a HTMLrepo
	HTMLrepo();
	//destructor
	~HTMLrepo() {};
	// writes to dogs.html the given input
	// input: an array with each  dog's data
	void writeToFile(vector<string> items) override;
	void pushOperation(string op, TElem obj) override;
	void emptyRepo() override;
	string lastOperation() override;
	TElem lastObj() override;
};

template<typename TElem>
inline HTMLrepo<TElem>::HTMLrepo() : repository<TElem>{ "dogs.html" } {}

template <typename TElem>
vector<string> HTMLrepo<TElem>::createFormat(string str, char delimiter) {
	vector<string> format;
	stringstream ss(str);
	string attr;
	while (getline(ss, attr, delimiter)) {
		format.push_back(attr);
	}
	return format;
}

template<typename TElem>
inline void HTMLrepo<TElem>::writeToFile(vector<string> items){
	ofstream f(this->fileType, ios::trunc);
	string html = "<!DOCTYPE html><html><head><title>Dogs</title></head><body><table border=\"1\"><tr><td>ID</td><td>Name</td><td>Breed</td><td>Age</td><td>link</td></tr>";
	for (string item : items) {
		html += "\n<tr>";
		vector<string> format = createFormat(item, ',');
		for (string attr : format) {
			html += "<td>" + attr + "</td>";
		}
		html += "</tr>";
	}
	html += "\n</table></body></html>";
	f << html;
	f.close();
}

template<typename TElem>
inline void HTMLrepo<TElem>::pushOperation(string op, TElem obj){}

template<typename TElem>
inline void HTMLrepo<TElem>::emptyRepo() {}

template<typename TElem>
inline string HTMLrepo<TElem>::lastOperation() { return string(); }

template<typename TElem>
inline TElem HTMLrepo<TElem>::lastObj(){ return TElem(); }
