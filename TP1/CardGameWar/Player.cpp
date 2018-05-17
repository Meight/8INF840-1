#include "Player.h"

Player::Player()
{
	m_deck = new Stack<Card>();
	m_earnings = new Stack<Card>();
}