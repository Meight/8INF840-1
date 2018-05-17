#include "Player.h"

#define NUMBERCARDS 100

class Game
{
private:

Player* m_firstPlayer;
Player* m_secondPlayer;
Stack<Card>* m_gameDeck;

public:

Player* getFirstPlayer()const { return m_firstPlayer;}
Player* getSecondPlayer()const { return m_secondPlayer;}

Stack<Card>* getGameDeck()const { return m_gameDeck; };

void createGameDeck();
void distribution(Stack<Card>* firstPlayerDeck, Stack<Card>* secondPlayerDeck);
//void turn();
static double countPoints(Stack<Card>* deck);

Game();
~Game();

};