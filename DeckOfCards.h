#pragma once
#include <queue>
#include <vector>
#include <memory>

#include "Card.h"

class DeckOfCards
{
public:
	DeckOfCards();
	~DeckOfCards();


private:
	/*std::queue<std::unique_ptr<Card>> shuffledDeck;
	std::vector<std::unique_ptr<Card>> initialDeck;*/

	std::queue<Card*> shuffledDeck;
	std::vector<Card*> initialDeck;

	void createDeck();
	void shuffleDeck();
	void fillQueueCards();

};

