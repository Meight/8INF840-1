#pragma once

#include <iostream>
#include <string>

using namespace std;

enum Color { BLUE, BROWN, GREEN };

class Person
{
public:
	string firstName;
	string lastName;
	int birthYear;
	Color eyeColor;

public:
	Person(const string &firstName, const string &lastName, int birthYear, Color eyeColor);
	~Person();

	const string &getFirstName() const;
	const string &getLastName() const;
	int getBirthYear() const;
	Color getEyeColor() const;
	friend std::ostream & operator<<(std::ostream & _stream, Person const & person);
	bool operator==(const Person & other);
};

