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

	std::queue<Card>& getDeck();
private:
	std::queue<Card> shuffledDeck;
	std::vector<Card> initialDeck;

	void createDeck();

};

