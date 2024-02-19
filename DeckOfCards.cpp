#include "DeckOfCards.h"
#include <iostream>

DeckOfCards::DeckOfCards()
{
	createDeck();
}

void DeckOfCards::createDeck()
{
	const std::string suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	const std::string face[13] =
	{ "Ace", "Deuce", "Three", "Four",
		"Five", "Six", "Seven", "Eight", "Nine",
		"Ten", "Jack", "Queen", "King" };

	for (int i = 0; i < 52; i++)
	{
		std::string cardId = std::to_string(i);
		std::string cardFace = face[i % 13];
		std::string cardSuit = suit[i / 13];

		initialDeck.emplace_back(new Card(cardFace, cardSuit, cardId));
	}
	std::cout << "Initial deck created.\n\n";
	shuffleDeck();
	fillQueueCards();
}

void DeckOfCards::shuffleDeck()
{
	std::srand(time(NULL));

	for (int i = 0; i < 52; i++)
	{
		int index = rand() % 52;
		Card* temp = initialDeck.at(i);
		initialDeck.at(i) = initialDeck.at(index);
		initialDeck.at(index) = temp;
	}
	std::cout << "Deck shuffled.\n\n";
}

void DeckOfCards::fillQueueCards()
{
	for (int i = 0; i < initialDeck.size(); i++)
	{
		shuffledDeck.push(initialDeck.at(i));
	}
	std::cout << shuffledDeck.size() << std::endl;
	std::cout << "Shuffled deck created.\n\n";
}

DeckOfCards::~DeckOfCards()
{
	std::cout << "Deck of cards destructor\n";

	for (auto& c : initialDeck) {
		shuffledDeck.pop();
		delete c;
		c = nullptr;
	}
	std::cout << shuffledDeck.size();
}