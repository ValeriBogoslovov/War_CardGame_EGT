#include "GameService.h"
#include <iostream>

void GameService::createPlayers()
{
	Player firstPlayer;
	firstPlayer.setPlayerID(0);
	Player secondPlayer;
	secondPlayer.setPlayerID(1);
	Player thirdPlayer;
	thirdPlayer.setPlayerID(2);

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
	if (players.at(0).isPlaying)
	{
		std::cout << players.at(0).getPlayerID() << ":\n"
			<< players.at(0).getPlayerDeck().front().getFace() << " of "
			<< players.at(0).getPlayerDeck().front().getSuit() << std::endl;
	}
	if (players.at(1).isPlaying)
	{
		std::cout << players.at(1).getPlayerID() << ":\n"
			<< players.at(1).getPlayerDeck().front().getFace() << " of "
			<< players.at(1).getPlayerDeck().front().getSuit() << std::endl;
	}
	if (players.at(2).isPlaying)
	{
		std::cout << players.at(2).getPlayerID() << ":\n"
			<< players.at(2).getPlayerDeck().front().getFace() << " of "
			<< players.at(2).getPlayerDeck().front().getSuit() << std::endl;
	}
}

void GameService::checkAndSetPlayerIfPlaying()
{
	if (players.at(0).getPlayerDeck().size() == 0)
	{
		players.at(0).isPlaying = false;
	}
	if (players.at(1).getPlayerDeck().size() == 0)
	{
		players.at(1).isPlaying = false;
	}
	if (players.at(2).getPlayerDeck().size() == 0)
	{
		players.at(2).isPlaying = false;
	}
}

void GameService::printPlayersCardPowers()
{
	int p1Power = 0;
	int p2Power = 0;
	int p3Power = 0;
	if (players.at(0).isPlaying && players.at(1).isPlaying && players.at(2).isPlaying)
	{
		p1Power = players.at(0).getPlayerDeck().front().getPower();
		p2Power = players.at(1).getPlayerDeck().front().getPower();
		p3Power = players.at(2).getPlayerDeck().front().getPower();

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
		else
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
	else if (players.at(0).isPlaying && players.at(1).isPlaying)
	{
		if (p1Power > p2Power)
		{
			discardedCards.push(players.at(0).getPlayerDeck().front());
			players.at(0).getPlayerDeck().pop();
			discardedCards.push(players.at(1).getPlayerDeck().front());
			players.at(1).getPlayerDeck().pop();

			int disSize = discardedCards.size();
			for (int i = 0; i < disSize; i++)
			{
				players.at(0).getPlayerDeck().push(discardedCards.front());
				discardedCards.pop();
			}
			std::cout << "Player 1 wins with power: " << p1Power << std::endl;
		}
		else
		{
			discardedCards.push(players.at(0).getPlayerDeck().front());
			players.at(0).getPlayerDeck().pop();
			discardedCards.push(players.at(1).getPlayerDeck().front());
			players.at(1).getPlayerDeck().pop();

			int disSize = discardedCards.size();
			for (int i = 0; i < disSize; i++)
			{
				players.at(1).getPlayerDeck().push(discardedCards.front());
				discardedCards.pop();
			}
			std::cout << "Player 2 wins with power: " << p2Power << std::endl;
		}
	}
	else if (players.at(0).isPlaying && players.at(2).isPlaying)
	{
		if (p1Power > p3Power)
		{
			discardedCards.push(players.at(0).getPlayerDeck().front());
			players.at(0).getPlayerDeck().pop();
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
		else
		{
			discardedCards.push(players.at(0).getPlayerDeck().front());
			players.at(0).getPlayerDeck().pop();
			discardedCards.push(players.at(1).getPlayerDeck().front());
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
	else if (players.at(1).isPlaying && players.at(2).isPlaying)
	{
		if (p2Power > p3Power)
		{
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
		else
		{
			discardedCards.push(players.at(1).getPlayerDeck().front());
			players.at(1).getPlayerDeck().pop();
			discardedCards.push(players.at(1).getPlayerDeck().front());
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
	checkAndSetPlayerIfPlaying();
}

void GameService::checkAndSetPlayersForWars()
{
	int p1Power = 0;
	int p2Power = 0;
	int p3Power = 0;

	if (players.at(0).isPlaying && players.at(1).isPlaying && players.at(2).isPlaying)
	{
		p1Power = players.at(0).getPlayerDeck().front().getPower();
		p2Power = players.at(1).getPlayerDeck().front().getPower();
		p3Power = players.at(2).getPlayerDeck().front().getPower();

		if (p1Power == p2Power && p1Power == p2Power)
		{
			players.at(0).isAtWar = true;
			players.at(1).isAtWar = true;
			players.at(2).isAtWar = true;
		}
	}
	else if (players.at(0).isPlaying && players.at(1).isPlaying)
	{
		p1Power = players.at(0).getPlayerDeck().front().getPower();
		p2Power = players.at(1).getPlayerDeck().front().getPower();

		if (p1Power == p2Power)
		{
			players.at(0).isAtWar = true;
			players.at(1).isAtWar = true;
		}
	}
	else if (players.at(0).isPlaying && players.at(2).isPlaying)
	{
		p1Power = players.at(0).getPlayerDeck().front().getPower();
		p3Power = players.at(2).getPlayerDeck().front().getPower();

		if (p1Power == p3Power)
		{
			players.at(0).isAtWar = true;
			players.at(2).isAtWar = true;
		}
	}
	else if (players.at(1).isPlaying && players.at(2).isPlaying)
	{
		p2Power = players.at(1).getPlayerDeck().front().getPower();
		p3Power = players.at(2).getPlayerDeck().front().getPower();

		if (p2Power == p3Power)
		{
			players.at(1).isAtWar = true;
			players.at(2).isAtWar = true;
		}
	}

}

void GameService::threePlayerWar()
{

}

void GameService::twoPlayerWar(int firstId, int secondID)
{

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
