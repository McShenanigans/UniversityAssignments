#include "exceptions.h"

myException::myException(string msg)
{
	this->msg = msg;
}

const char * myException::what() const noexcept
{
	return this->msg.c_str();
}

myException::~myException()
{
}
