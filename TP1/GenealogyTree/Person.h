#pragma once

#include <iostream>
#include <string>

using namespace std;

enum Gender { MALE, FEMALE };
enum Color { BLUE, BROWN, GREEN };

class Person
{
public:
	string firstName;
	string lastName;
	int birthYear;
	Color eyeColor;

protected:
	Gender gender;

public:
	Person(const string &firstName, const string &lastName, int birthYear, Color eyeColor);
	~Person();

	const string &getFirstName() const;
	const string &getLastName() const;
	int getBirthYear() const;
	int getAge() const;
	Color getEyeColor() const;
	Gender getGender() const;
	friend std::ostream & operator<<(std::ostream & _stream, Person const & person);
	bool operator==(const Person & other);
};

class Male : public Person {
public:
	Male(const string &firstName, const string &lastName, int birthYear, Color eyeColor);
};

class Female : public Person {
public:
	Female(const string &firstName, const string &lastName, int birthYear, Color eyeColor);
};