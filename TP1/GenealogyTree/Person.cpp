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