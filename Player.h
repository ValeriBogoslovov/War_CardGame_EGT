#pragma once
#include "Card.h"
#include <queue>

class Player
{
public:
	void addCard(Card c);
	void setPlayerID(int id);

	std::queue<Card>& getPlayerDeck();
	int getPlayerID() const;

	bool isPlaying = true;
	bool hasWonGame = false;
	bool hasWonWar = false;
	bool isAtWar = false;

private:
	std::queue<Card> playerDeck;
	int playerID;
};

