#pragma once
#include "Card.h"
#include <queue>

class Player
{
public:

private:
	std::queue<Card*> playerDeck;
	int playerPoints = 0;
};

