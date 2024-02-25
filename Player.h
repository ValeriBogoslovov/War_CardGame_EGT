#pragma once

#include "Card.h"
#include <queue>
#include <stack>

class Player
{
public:
	//setters, updaters
	void addCard(Card c);
	void setPlayerID(int id);
	void updateAtWar(bool isAtWar);
	void setCardAngle(double angle);
	void setPlayerBackCardPosX(int posX);
	void setPlayerBackCardPosY(int posY);
	void setPlayerFaceUpCardPosX(int posX);
	void setPlayerFaceUpCardPosY(int posY);
	std::queue<Card>& updatePlayerDeck();
	std::stack<Card>& updatePlayerDiscardedDeck();

	// getters
	std::queue<Card> getPlayerDeck() const;
	std::stack<Card> getPlayerDiscardedDeck() const;
	int getPlayerID() const;
	bool getAtWar()const;
	double getCardAngle()const;
	int getPlayerBackCardPosX()const;
	int getPlayerBackCardPosY()const;
	int getPlayerFaceUpCardPosX()const;
	int getPlayerFaceUpCardPosY()const;

	bool playerAtWar = false;

	enum PlayerState {
		PlayerReady,
		PlayerCardOpen,
		WonBattle,
		Inactive,
		Finished
	};
	PlayerState playerState;

private:
	std::queue<Card> playerDeck;
	std::stack<Card> playerDiscardedCards;
	int playerID;
	double playerCardAngle;
	bool isAtWar = false;

	// player back and face up card position x and y
	int playerBackCardPosX;
	int playerBackCardPosY;
	int playerFaceCardPosX;
	int playerFaceCardPosY;
};

