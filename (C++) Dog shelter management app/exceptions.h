#pragma once
#include <exception>
#include <string>
using namespace std;

// custom exception class
class myException : public exception {
private:
	string msg;
public:
	// constructor
	// input: the message for the error
	myException(string msg);

	// returns the message of the error
	const char* what() const noexcept override;

	// destructor
	~myException();
};