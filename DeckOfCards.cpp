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
		//initialDeck.push_back(std::make_unique<Card>(cardFace, cardSuit, cardId));
		initialDeck.emplace_back(std::make_unique<Card>(cardId, cardFace, cardSuit));
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


		initialDeck.at(i) = std::move(initialDeck.at(index));
		initialDeck.at(index) = std::move(initialDeck.at(i));
		//Card* temp = initialDeck.at(i);
		//initialDeck.at(i) = initialDeck.at(index);
		//initialDeck.at(index) = temp;
		//std::cout << temp->getFace() << "-" << temp->getSuit() << std::endl;
		//temp = nullptr;
	}
	
	std::cout << "Deck shuffled.\n\n";
}

void DeckOfCards::fillQueueCards()
{
	for (int i = 0; i < initialDeck.size(); i++)
	{
		/*shuffledDeck.emplace(initialDeck.at(i).get());*/
		/*shuffledDeck.push(initialDeck.at(i));*/
	}

	std::cout << shuffledDeck.size() << std::endl;
	std::cout << "Shuffled deck created.\n\n";
}


DeckOfCards::~DeckOfCards()
{
	//for (auto& c : initialDeck) {
	//	delete c;
	//	c = nullptr;
	//}
	//int queueSize = shuffledDeck.size();
	//for (int i = 0; i < queueSize; i++)
	//{
	//	shuffledDeck.pop();
	//}
}