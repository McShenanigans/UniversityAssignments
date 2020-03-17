#include "dogValidator.h"



dogValidator::dogValidator()
{
}

void dogValidator::validate(const Dog & d)
{
	if (d.getName() == "") throw dogValidatorException("invalid dog");
	if (d.getBreed() == "") throw dogValidatorException("invalid dog");
	if (d.getPhoto() == "") throw dogValidatorException("invalid dog");
	if (d.getAge() == -1) throw dogValidatorException("invalid dog");
	if (d.getID() == -1) throw dogValidatorException("invalid dog");
}


dogValidator::~dogValidator()
{
}

dogValidatorException::dogValidatorException(string msg)
{
	this->msg = msg;
}

const char * dogValidatorException::what() const noexcept
{
	return this->msg.c_str();
}

dogValidatorException::~dogValidatorException()
{
}
