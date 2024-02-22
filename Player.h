#pragma once
#include "Card.h"
#include <queue>

class Player
{
public:
	void addCard(Card c);
	void setPlayerID(int id);

	// get deck const
	std::queue<Card> getPlayerDeck();

	//update deck
	std::queue<Card>& updatePlayerDeck();
	int getPlayerID() const;

	//bool isPlaying = true;
	//bool hasWonGame = false;
	//bool hasWonWar = false;

	bool isAtWar = false;

private:
	std::queue<Card> playerDeck;
	int playerID;
};

