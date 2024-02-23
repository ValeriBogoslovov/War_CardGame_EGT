#pragma once
#include <queue>
#include <vector>
#include <memory>

#include "Card.h"

class DeckOfCards
{
public:
	void createDeck();
	std::queue<Card> getDeck() const;
	std::queue<Card>& updateDeck();
private:
	std::queue<Card> shuffledDeck;
	std::vector<Card> initialDeck;

};

