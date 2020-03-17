#pragma once
#include <exception>
#include <string>
#include "Dog.h"
using namespace std;

// exception class; thrown when dog is invalid
class dogValidatorException : public exception {
private:
	string msg;
public:
	// costructor
	// input: the message for the exception
	dogValidatorException(string  msg);
	
	// returns the message of the exception
	const char* what() const noexcept override;

	// destructor
	~dogValidatorException();
};

class dogValidator
{
public:
	// constructor
	dogValidator();

	// validates a dog object;
	// input: the dog
	static void validate(const Dog& s);
	
	// destructor
	~dogValidator();
};

