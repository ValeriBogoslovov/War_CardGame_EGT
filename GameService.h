#pragma once

#include "Player.h"
#include "DeckOfCards.h"


class GameService
{
public:

	void createPlayers();
	void dealCardsToPlayers();
	void putCardToTable();
	void checkPlayersCards();

	Card drawCard();

	std::vector<Player>& getPlayers();
	std::queue<Card>& getDiscardedCards();

	bool playerWon = false;
	bool isWar = false;

private:
	std::vector<Player> players;
	std::queue<Card> discardedCards;
	DeckOfCards deck;
};

