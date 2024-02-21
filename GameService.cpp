#include "GameService.h"
#include <iostream>

void GameService::createPlayers()
{
	Player firstPlayer;
	firstPlayer.setPlayerID("Player 1");
	Player secondPlayer;
	secondPlayer.setPlayerID("Player 2");
	Player thirdPlayer;
	thirdPlayer.setPlayerID("Player 3");

	players.push_back(firstPlayer);
	players.push_back(secondPlayer);
	players.push_back(thirdPlayer);
}

void GameService::dealCardsToPlayers()
{
	for (int i = 0; i < 10; i++)
	{
		players.at(0).addCard(deck.getDeck().front());
		deck.getDeck().pop();
		players.at(1).addCard(deck.getDeck().front());
		deck.getDeck().pop();
		players.at(2).addCard(deck.getDeck().front());
		deck.getDeck().pop();
	}
}

void GameService::putCardToTable()
{
	std::cout << players.at(0).getPlayerID() << ":\n"
		<< players.at(0).getPlayerDeck().front().getFace() << " of "
		<< players.at(0).getPlayerDeck().front().getSuit() << std::endl;

	std::cout << players.at(1).getPlayerID() << ":\n"
		<< players.at(1).getPlayerDeck().front().getFace() << " of "
		<< players.at(1).getPlayerDeck().front().getSuit() << std::endl;

	std::cout << players.at(2).getPlayerID() << ":\n"
		<< players.at(2).getPlayerDeck().front().getFace() << " of "
		<< players.at(2).getPlayerDeck().front().getSuit() << std::endl;
}

void GameService::checkPlayersCards()
{
	int p1Power = players.at(0).getPlayerDeck().front().getPower();
	int p2Power = players.at(1).getPlayerDeck().front().getPower();
	int p3Power = players.at(2).getPlayerDeck().front().getPower();

	if (p1Power > p2Power && p1Power > p3Power)
	{
		discardedCards.push(players.at(0).getPlayerDeck().front());
		players.at(0).getPlayerDeck().pop();
		discardedCards.push(players.at(1).getPlayerDeck().front());
		players.at(1).getPlayerDeck().pop();
		discardedCards.push(players.at(2).getPlayerDeck().front());
		players.at(2).getPlayerDeck().pop();

		int disSize = discardedCards.size();
		for (int i = 0; i < disSize; i++)
		{
			players.at(0).getPlayerDeck().push(discardedCards.front());
			discardedCards.pop();
		}
		std::cout << "Player 1 wins with power: " << p1Power << std::endl;
	}
	else if (p2Power > p1Power && p2Power > p3Power)
	{
		discardedCards.push(players.at(0).getPlayerDeck().front());
		players.at(0).getPlayerDeck().pop();
		discardedCards.push(players.at(1).getPlayerDeck().front());
		players.at(1).getPlayerDeck().pop();
		discardedCards.push(players.at(2).getPlayerDeck().front());
		players.at(2).getPlayerDeck().pop();

		int disSize = discardedCards.size();
		for (int i = 0; i < disSize; i++)
		{
			players.at(1).getPlayerDeck().push(discardedCards.front());
			discardedCards.pop();
		}
		std::cout << "Player 2 wins with power: " << p2Power << std::endl;
	}
	else if (p3Power > p1Power && p3Power > p2Power)
	{
		discardedCards.push(players.at(0).getPlayerDeck().front());
		players.at(0).getPlayerDeck().pop();
		discardedCards.push(players.at(1).getPlayerDeck().front());
		players.at(1).getPlayerDeck().pop();
		discardedCards.push(players.at(2).getPlayerDeck().front());
		players.at(2).getPlayerDeck().pop();

		int disSize = discardedCards.size();
		for (int i = 0; i < disSize; i++)
		{
			players.at(2).getPlayerDeck().push(discardedCards.front());
			discardedCards.pop();
		}
		std::cout << "Player 3 wins with power: " << p3Power << std::endl;
	}
}

Card GameService::drawCard()
{
	Card c = deck.getDeck().front();
	deck.getDeck().pop();
	return c;
}

std::vector<Player>& GameService::getPlayers()
{
	return this->players;
}

std::queue<Card>& GameService::getDiscardedCards()
{
	return this->discardedCards;
}
