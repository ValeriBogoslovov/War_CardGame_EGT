#include <iostream>
#include <algorithm> // needed for std::shuffle()
#include <random> // needed for std::random_device and std::mt19937

#include "DeckOfCards.h"

void DeckOfCards::createDeck()
{
	const std::string suit[4] = { "Spades", "Diamonds", "Hearts", "Clubs" };
	// clear queue
	const std::string face[13] =
	{ "Deuce", "Three", "Four",
		"Five", "Six", "Seven", "Eight", "Nine",
		"Ten", "Jack", "Queen", "King", "Ace" };

	// fill initial vector deck
	for (int i = 0; i < 52; i++)
	{
		std::string cardId = std::to_string(i);
		std::string cardFace = face[i % 13];
		std::string cardSuit = suit[i / 13];
		int cardPower = (i % 13) + 2;
		Card c(cardFace, cardSuit, cardId, cardPower);
		initialDeck.push_back(c);
	}
	std::cout << "Initial deck created.\n\n";
	// uniformly-distributed integer random number generator
	std::random_device rdSeed;

	// random number engine based on Mersenne Twister algorithm
	std::mt19937 rngGenerator(rdSeed());

	// shuffle vector deck
	std::shuffle(initialDeck.begin(), initialDeck.end(), rngGenerator);
	std::cout << "Initial deck shuffled.\n\n";

	for (auto c : initialDeck) {
		shuffledDeck.push(c);
	}
	initialDeck.clear();

	std::cout << "Cards queue filled.\n\n";
}

std::queue<Card>& DeckOfCards::updateDeck()
{
	return this->shuffledDeck;
}

std::queue<Card> DeckOfCards::getDeck() const
{
	return this->shuffledDeck;
}