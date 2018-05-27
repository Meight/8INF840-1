#include "stdafx.h"
#include "Person.h"

Person::Person(const string &firstName, const string &lastName, int birthYear, Color eyeColor) :
	firstName(firstName), lastName(lastName), birthYear(birthYear), eyeColor(eyeColor) {}

Person::~Person() {}

const string &Person::getFirstName() const {
	return firstName;
}

const string &Person::getLastName() const {
	return lastName;
}

int Person::getBirthYear() const {
	return birthYear;
}

Color Person::getEyeColor() const {
	return eyeColor;
}

Gender Person::getGender() const
{
	return gender;
}

bool Person::operator==(const Person & other)
{
	return other.firstName == firstName && other.lastName == lastName && other.birthYear == birthYear;
}

std::ostream & operator<<(std::ostream & _stream, Person const & person)
{
	_stream << person.getFirstName() << " " << person.getLastName();
	return _stream;
}
