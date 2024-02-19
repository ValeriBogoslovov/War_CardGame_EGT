#pragma once
#include <queue>
#include <vector>

#include "Card.h"

class DeckOfCards
{
public:
	DeckOfCards();
	~DeckOfCards();
	void createDeck();

private:
	std::queue<Card*> shuffledDeck;

	std::vector<Card*> initialDeck;

	void shuffleDeck();
	void fillQueueCards();

};

