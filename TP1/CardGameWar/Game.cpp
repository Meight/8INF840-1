#include "Game.h"

#include <iostream>
#include <ctime>

Game::Game()
{
	m_firstPlayer = new Player();
	m_secondPlayer = new Player();

	m_gameDeck = new Stack<Card>();

	createGameDeck();
	distribution(m_firstPlayer->getDeck(), m_secondPlayer->getDeck());
}

void Game::createGameDeck()
{
	for (int i = 0; i < NUMBERCARDS; i++)
	{
		m_gameDeck->push(Card());
	}
}

void Game::distribution(Stack<Card>* firstPlayerDeck, Stack<Card>* secondPlayerDeck)
{
	int counter = 0;
	while (!m_gameDeck->isEmpty())
	{
		if (counter % 2 == 0)
			m_firstPlayer->getDeck()->push(m_gameDeck->pop());
		else
			m_secondPlayer->getDeck()->push(m_gameDeck->pop());

		counter++;
	}
}

double Game::countPoints(Stack<Card>* deck)
{
	double sum = 0;
	Card tempCard;
	while (!deck->isEmpty())
	{
		tempCard = deck->pop();

		if (tempCard.getColor() == RED)
			sum += 1.5*tempCard.getBonus()*tempCard.getValue();
		else
			sum+= tempCard.getBonus()*tempCard.getValue();
	}

	return sum;
}

int main(void)
{
	srand(time(NULL));

	Game* game = new Game();

	Stack<Card>* firstPlayerDeck = game->getFirstPlayer()->getDeck();
	Stack<Card>* secondPlayerDeck = game->getSecondPlayer()->getDeck();

	Stack<Card>* firstPlayerEarnings = game->getFirstPlayer()->getEarnings();
	Stack<Card>* secondPlayerEarnings = game->getSecondPlayer()->getEarnings();

	Card firstPlayerCard;
	Card secondPlayerCard;

	while (!firstPlayerDeck->isEmpty())
	{
		firstPlayerCard = firstPlayerDeck->pop();
		secondPlayerCard = secondPlayerDeck->pop();

		if (firstPlayerCard.getValue() > secondPlayerCard.getValue())
		{
			firstPlayerEarnings->push(firstPlayerCard);
			firstPlayerEarnings->push(secondPlayerCard);
		}

		if (firstPlayerCard.getValue() < secondPlayerCard.getValue())
		{
			secondPlayerEarnings->push(firstPlayerCard);
			secondPlayerEarnings->push(secondPlayerCard);
		}

		if (firstPlayerCard.getValue() == secondPlayerCard.getValue())
		{
			if (firstPlayerCard.getColor() == secondPlayerCard.getColor())
			{
				firstPlayerEarnings->push(firstPlayerCard);
				secondPlayerEarnings->push(secondPlayerCard);
			}

			else
			{
				if (firstPlayerCard.getColor() == RED)
				{
					firstPlayerEarnings->push(firstPlayerCard);
					firstPlayerEarnings->push(secondPlayerCard);
				}

				else
				{
					secondPlayerEarnings->push(firstPlayerCard);
					secondPlayerEarnings->push(secondPlayerCard);
				}
			}
		}
	}

	double firstPlayerPoints = Game::countPoints(firstPlayerEarnings);
	double secondPlayerPoints = Game::countPoints(secondPlayerEarnings);

	if (firstPlayerPoints > secondPlayerPoints)
		std::cout << "Le premier joueur l'emporte avec " << firstPlayerPoints << " points contre " << secondPlayerPoints << " points.\n";

	if (firstPlayerPoints < secondPlayerPoints)
		std::cout << "Le second joueur l'emporte avec " << secondPlayerPoints << " points contre " << firstPlayerPoints << " points.\n";

	if (firstPlayerPoints == secondPlayerPoints)
		std::cout << "Le jeu se solde par une égalité avec " << firstPlayerPoints << " points.\n";

	system("PAUSE");
}