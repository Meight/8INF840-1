#pragma once

#include "Stack.h"
#include "Card.h"

class Player
{
private:

	Stack<Card>* m_deck;
	Stack<Card>* m_earnings;

public:

	Stack<Card>* getDeck()const{ return m_deck; }
	Stack<Card>* getEarnings()const { return m_earnings; }

	Player();
	~Player();
};
