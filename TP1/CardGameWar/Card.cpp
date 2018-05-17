#include "Card.h"

Card::Card()
{
	m_bonus = rand() % CARDMAXBONUS + CARDMINBONUS;
	m_value = rand() % CARDMAXVALUE + CARDMINVALUE;
	m_color = Color(rand() % 2);
}