#pragma once

#include <iostream>

#define CARDMAXVALUE 10
#define CARDMINVALUE 1

#define CARDMAXBONUS 4
#define CARDMINBONUS 1

enum Color { RED, BLACK };

class Card
{
private:
	int m_bonus;
	int m_value;
	Color m_color;
	
public:

	int getBonus()const { return m_bonus; }
	int getValue()const { return m_value; }
	Color getColor()const { return m_color; }

	Card();
	//~Card();
};
