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
		//initialDeck.emplace_back(std::make_unique<Card>(cardId, cardFace, cardSuit));
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
		//std::string tempFace = initialDeck.at(i).get()->getFace();
		//std::string tempSuit =  initialDeck.at(i).get()->getSuit();
		//std::string tempID =  initialDeck.at(i).get()->getID();
		//std::unique_ptr<Card> temp = std::make_unique<Card>(tempFace,tempSuit,tempID);
		//initialDeck.at(i).swap(initialDeck.at(index));
		//initialDeck.at(index).swap(temp);
		Card* temp = initialDeck.at(i);
		initialDeck.at(i) = initialDeck.at(index);
		initialDeck.at(index) = temp;
		std::cout << temp->getFace() << "-" << temp->getSuit() << std::endl;
	}
	std::cout << "Deck shuffled.\n\n";
}

void DeckOfCards::fillQueueCards()
{
	for (int i = 0; i < initialDeck.size(); i++)
	{
		/*shuffledDeck.emplace(initialDeck.at(i).get());*/
		shuffledDeck.push(initialDeck.at(i));
	}

	std::cout << shuffledDeck.size() << std::endl;
	std::cout << "Shuffled deck created.\n\n";
}


DeckOfCards::~DeckOfCards()
{
	for (auto& c : initialDeck) {
		delete c;
		c = nullptr;
	}
	int queueSize = shuffledDeck.size();
	for (int i = 0; i < queueSize; i++)
	{
		shuffledDeck.pop();
	}
}