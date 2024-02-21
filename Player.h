#pragma once
#include "Card.h"
#include <queue>

class Player
{
public:
	void addCard(Card c);
	void setPlayerID(std::string id);

	std::queue<Card>& getPlayerDeck();
	//std::queue<Card>& getDicardedDeck();
	std::string getPlayerID() const;

private:
	std::queue<Card> playerDeck;
	//std::queue<Card> discardedCards;
	int playerPoints = 0;
	std::string playerID;
};

