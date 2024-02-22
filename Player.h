#pragma once
#include "Card.h"
#include <queue>

class Player
{
public:
	//setters, updaters
	void addCard(Card c);
	void setPlayerID(int id);
	void updateAtWar(bool isAtWar);
	std::queue<Card>& updatePlayerDeck();

	// getters
	std::queue<Card> getPlayerDeck() const;
	int getPlayerID() const;
	bool getAtWar()const;

private:
	std::queue<Card> playerDeck;
	int playerID;
	bool isAtWar = false;
};

